#include "tcpserver.hpp"
#include "socket.hpp"
#include <stdexcept>
#include <iostream>
#include <stdio.h>

namespace hermes
{
    TcpServer::TcpServer()
    {
        this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->server_fd < 0)
        {
            std::cerr << "Failed to initialize socket" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    TcpServer::TcpServer(IPAddress ip_address)
    {
        this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->server_fd < 0)
        {
            std::cerr << "Failed to initialize socket" << std::endl;
            exit(EXIT_FAILURE);
        }

        if(!this->Bind(ip_address))
        {
            std::cerr << "Failed to bind socket to IP Address" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (!this->Listen())
        {
            std::cerr << "Failed to start listening" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    bool TcpServer::Bind(IPAddress ip_address)
    {
        int opt = 1;
        if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEPORT , &opt, sizeof(opt)) < 0)
        {
            printf("Failure to perform setsockopt\n");
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0)
        {
            printf("Failure to perform setsockopt\n");
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        if (int code = bind(this->server_fd, ip_address.GetSockAddr(),
            ip_address.GetSockAddrLen()) < 0)
        {
            printf("Bind operation failed\nError code %d\n", code);
            exit(EXIT_FAILURE);
        }

        return true;
    }
    bool TcpServer::Listen()
    {
        if (listen(this->server_fd, this->backlog) < 0)
        {
            printf("Listening operation failed\n");
            return false;
        }
        return true;
    }

    bool TcpServer::BindAndListen(IPAddress ip_address)
    {
        bool bind_flag = this->Bind(ip_address);
        bool listen_flag = this->Listen();

        return bind_flag && listen_flag;
    }
    TcpClient TcpServer::Accept()
    {
        Socket connected_socket = Socket();
        socklen_t addr_len = ip_address.GetSockAddrLen();
        connected_socket.SetSocketFD(
            accept(this->server_fd, this->ip_address.GetSockAddr(), &addr_len));

        if (connected_socket.GetSocketFD() < 0)
        {
            std::cerr << "Failed to initialize socket" << std::endl;
        }
        TcpClient client = TcpClient(connected_socket);
        return client;
    }
    bool TcpServer::Close(TcpClient client)
    {
        return client.Close();
    }

    bool TcpServer::Shutdown()
    {
        int ret = shutdown(this->server_fd, SHUT_RDWR);
        return ret == 0;
    }

    void TcpServer::Send(TcpClient client, std::string msg)
    {
        client.Send(msg);
    }
    std::string TcpServer::Receive(TcpClient client, uint32_t buff_size)
    {
        return client.Receive(buff_size);
    }
    uint32_t TcpServer::DataAvailable(TcpClient client)
    {
        return client.DataAvailable();
    }
}
