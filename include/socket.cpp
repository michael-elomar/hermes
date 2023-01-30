#include "socket.hpp"
#include <stdexcept>
#include <iostream>
#include <stdio.h>

namespace hermes
{
    Socket::Socket()
    {
        this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->socket_fd < 0)
        {
            std::cerr << "Failed to initialize socket" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    std::string Socket::Receive(uint32_t buff_size)
    {
        char *buffer = (char*) malloc((size_t)buff_size);
        read(this->socket_fd, buffer, 1024);
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

    int Socket::GetSocketFD()
    {
        return this->socket_fd;
    }
    void Socket::SetSocketFD(int socket_fd)
    {
        this->socket_fd = socket_fd;
    }
    uin32_T Socket::DataAvailable()
    {
        int count;
        ioctl(this->socket_fd, FIONREAD, &count);
        return count;
    }
}

