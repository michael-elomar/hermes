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

        struct sockaddr_in sock_addr = ip_address.GetSockAddr();
        if (int code = bind(this->socket_fd,
            (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0)
        {
            printf("Bind operation failed\nError code %d\n", code);
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

        struct sockaddr_in sock_addr = ip_address.GetSockAddr();
        if (int code = bind(this->socket_fd,
            (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0)
        {
            printf("Bind operation failed\nError code %d\n", code);
            exit(EXIT_FAILURE);
        }

        return true;
    }
}
