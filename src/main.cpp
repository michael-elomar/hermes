#include <stdio.h>

// local includes

#include "../include/hermes.h"
using namespace hermes;
int main(int argc, char **argv)
{
    IPAddress ip_addr = IPAddress("127.0.0.1");
    std::cout << ip_addr.GetIPAddress() << std::endl;

    TcpServer server = TcpServer(ip_addr);
    TcpClient client = server.Accept();
    std::cout << server.Receive(client, server.DataAvailable(client)) << std::endl;
    server.Close(client);
    server.Shutdown();
}