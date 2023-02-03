#ifndef TCPSCLIENT_HPP
#define TCPSCLIENT_HPP
#include "socket.hpp"
#include "ipaddress.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace hermes
{
    class TcpClient
    {
        public:
            TcpClient();
            TcpClient(IPAddress ip_address);
            TcpClient(Socket socket);
            bool Connect(IPAddress ip_address);
            bool Close();
            void Send(std::string msg);
            std::string Receive(uint32_t buff_size);
            uint32_t DataAvailable();


        private:
            int client_fd;
            Socket connected_socket;
            IPAddress ip_address;
    };
}

#endif // TCPSCLIENT_HPP
