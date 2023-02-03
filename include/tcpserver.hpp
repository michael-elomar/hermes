#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP
#include "socket.hpp"
#include "ipaddress.hpp"
#include "tcpclient.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

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
            TcpClient Accept();
            void Send(TcpClient client, std::string msg);
            std::string Receive(TcpClient client, uint32_t buff_size);
            bool Close(TcpClient client);
            bool Shutdown();
            uint32_t DataAvailable(TcpClient client);


        private:
            int server_fd;
            std::vector<TcpClient> clients;
            IPAddress ip_address;
            uint16_t backlog = 10;
    };
}

#endif // TCPSERVER_HPP
