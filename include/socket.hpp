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
            Socket(uint8_t comm_type, uint8_t socket_type);

            // initializes a socket with a protocol
            Socket(uint8_t protocol, uint8_t socket_type, uint8_t comm_type);

            // init an socket and bind it to an xIP address
            Socket(uint8_t comm_type, IPAddress ip_address);

            bool Bind(IPAddress ip_address);
            bool Listen();
            Socket Accept();
            bool Close();


        private:
            int socket_fd;
            IPAddress ip_address;
            uint8_t protocol, comm_type;
            uint16_t backlog = 10;
    };
}

#endif // SOCKET_HPP
