#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "ipaddress.hpp"
#include <sys/ioctl.h>


namespace hermes
{
    class Socket
    {
        public:
            Socket();
            bool Close();
            bool Shutdown();
            void Send(std::string msg);
            std::string Receive(uint32_t buff_size);
            void SetSocketFD(int socket_fd);
            int GetSocketFD();
            uint32_t DataAvailable();

        private:
            int socket_fd;
            uint8_t comm_type, socket_type;
    };
}

#endif // SOCKET_HPP
