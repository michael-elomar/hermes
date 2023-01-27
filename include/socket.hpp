#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "ipaddress.hpp"


namespace hermes
{
    enum IProtocol
    {
        LOCAL,
        IPV4,
        IPV6
    };
    enum CommType
    {
        TCP,
        UDP
    };
    enum SocketType
    {
        SERVER,
        CLIENT
    };

    class Socket
    {
        public:
            // init a socket with either TCP or UDP comm type
            // defaults to local communication protocol
            Socket() {}
            Socket(uint8_t comm_type, uint8_t socket_type);

            // initializes a socket with a protocol
            Socket(uint8_t comm_type, uint8_t socket_type, IPAddress ip_address);

            // init an socket and bind it to an IP address
            Socket(uint8_t comm_type, IPAddress ip_address);

            bool Bind(IPAddress ip_address);
            bool Listen();
            bool BindAndListen(IPAddress ip_address);
            Socket Accept();
            bool Connect(IPAddress ip_address);
            bool Close();
            bool Shutdown();
            void Send(std::string msg);
            std::string Receive(uint16_t buff_size);



        public:
            void SetSocketFD(int socket_fd);

        private:
            int socket_fd;
            IPAddress ip_address;
            uint8_t comm_type, socket_type;
            uint16_t backlog = 10;
    };
}

#endif // SOCKET_HPP
