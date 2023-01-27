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
    }
}
