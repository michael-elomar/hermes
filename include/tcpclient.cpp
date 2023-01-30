#include "tcpclient.hpp"
#include "socket.hpp"
#include <stdexcept>
#include <iostream>
#include <stdio.h>

namespace hermes
{
    TcpClient::TcpClient()
    {
        this->client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->client_fd < 0)
        {
            std::cerr << "Failed to initialize socket" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    TcpClient::TcpClient(IPAddress ip_address)
    {
        this->client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->client_fd < 0)
        {
            std::cerr << "Failed to initialize socket" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->Connect(ip_address);
    }

    bool TcpClient::Connect(IPAddress ip_address)
    {
        int connection_fd = connect(this->client_fd, ip_address.GetSockAddr(), ip_address.GetSockAddrLen());
        if (connection_fd < 0)
        {
            std::cerr << "Connection failed\n";
            return false;
        }
        this->connected_socket = Socket();
        this->connected_socket.SetSocketFD(connection_fd);
        return true;
    }

    void TcpClient::Send(std::string msg)
    {
        const char *buffer = msg.c_str();
        send(this->client_fd, buffer, strlen(buffer), 0);
    }
    std::string TcpClient::Receive(uint32_t buff_size)
    {
        char *buffer = (char*) malloc((size_t)buff_size);
        read(this->client_fd, buffer, 1024);
        std::string msg = std::string(buffer);
        free(buffer);
        return msg;
    }

    bool TcpClient::Close()
    {
        return this->connected_socket.Close();
    }
    uin32_t TcpClient::DataAvailable()
    {
        int count;
        ioctl(this->client_fd, FIONREAD, &count);
        return count;
    }
}
