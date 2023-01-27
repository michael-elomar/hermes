#include <stdio.h>

// local includes

#include "../include/hermes.h"
using namespace hermes;
int main(int argc, char **argv)
{
    IPAddress ip_addr = IPAddress("127.0.0.1");
    std::cout << ip_addr.GetIPAddress() << std::endl;
    Socket socket = Socket(CommType::TCP, SocketType::SERVER);
    /*(if(!socket.BindAndListen(ip_addr))
    {
        std::cerr << "Failed to bind and listen on" << std::endl;
    }*/

    socket.Connect(ip_addr);
    socket.Send("Hello world");
    std::string msg = socket.Receive(1024);
    std::cout << msg << std::endl;
    socket.Close();
}