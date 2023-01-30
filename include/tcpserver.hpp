#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP
#include "socket.hpp"
#include "ipaddress.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace hermes
{
    class TcpServer
    {
        public:
            TcpServer();
            TcpServer(IPAddress ip_address);
            bool Bind(IPAddress ip_address);
            bool Listen();
            bool BindAndListen(IPAddress ip_address);
            bool Accept();
            void Send(std::string msg);
            std::string Receive(uint32_t buff_size);
            bool Close();
            bool Shutdown();
            uint32_t DataAvailable();


        private:
            int server_fd;
            Socket connected_socket;
            IPAddress ip_address;
            uint16_t backlog = 10;
    };
}

#endif // TCPSERVER_HPP
