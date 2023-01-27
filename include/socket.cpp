#include "socket.hpp"
#include <stdexcept>
#include <iostream>


namespace hermes
{
    Socket::Socket(uint8_t comm_type, uint8_t socket_type)
    {
        if (comm_type == CommType::TCP)
            this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        else
            this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

        if (this->socket_fd < 0)
        {
            std::cerr << "Failed to initialize socket" << std::endl;
            exit(EXIT_FAILURE);
        }

        this->socket_type = socket_type;
    }
    Socket::Socket(uint8_t comm_type, uint8_t socket_type, IPAddress ip_address)
    {
        if (comm_type == CommType::TCP)
            this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        else
            this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

        if (this->socket_fd < 0)
        {
            std::cerr << "Failed to initialize socket" << std::endl;
            exit(EXIT_FAILURE);
        }
        this->socket_type = socket_type;

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
    bool Socket::Bind(IPAddress ip_address)
    {
        int opt = 1;
        if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEPORT , &opt, sizeof(opt)) < 0)
        {
            printf("Failure to perform setsockopt\n");
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0)
        {
            printf("Failure to perform setsockopt\n");
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        if (int code = bind(this->socket_fd, ip_address.GetSockAddr(),
            ip_address.GetSockAddrLen()) < 0)
        {
            printf("Bind operation failed\nError code %d\n", code);
            exit(EXIT_FAILURE);
        }

        return true;
    }
    bool Socket::Listen()
    {
        if (listen(this->socket_fd, this->backlog) < 0)
        {
            printf("Listening operation failed\n");
            return false;
        }
        return true;
    }

    bool Socket::BindAndListen(IPAddress ip_address)
    {
        bool bind_flag = this->Bind(ip_address);
        bool listen_flag = this->Listen();

        return bind_flag && listen_flag;
    }

    void Socket::SetSocketFD(int socket_fd)
    {
        this->socket_fd = socket_fd;
    }

    Socket Socket::Accept()
    {
        Socket new_socket = Socket();
        socklen_t addr_len = ip_address.GetSockAddrLen();
        new_socket.SetSocketFD(
            accept(this->socket_fd, this->ip_address.GetSockAddr(), &addr_len));

        if (new_socket.socket_fd < 0)
        {
            std::cerr << "Failed to initialize socket" << std::endl;
            exit(EXIT_FAILURE);
        }
        return new_socket;
    }

    std::string Socket::Receive(uint16_t buff_size)
    {
        char *buffer = (char*) malloc((size_t)buff_size);
        int valread = read(this->socket_fd, buffer, 1024);
        std::string msg = std::string(buffer);
        free(buffer);
        return msg;
    }
    void Socket::Send(std::string msg)
    {
        const char *buffer = msg.c_str();
        send(this->socket_fd, buffer, strlen(buffer), 0);
    }

    bool Socket::Close()
    {
        int ret = close(this->socket_fd);
        return ret == 0;
    }

    bool Socket::Shutdown()
    {
        int ret = shutdown(this->socket_fd, SHUT_RDWR);
        return ret == 0;
    }

    bool Socket::Connect(IPAddress ip_address)
    {
        int client_fd = connect(this->socket_fd, ip_address.GetSockAddr(), ip_address.GetSockAddrLen());
        if (client_fd < 0)
        {
            std::cerr << "Connection failed\n";
            return false;
        }
        return true;
    }
}

