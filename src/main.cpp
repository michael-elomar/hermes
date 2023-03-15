#include <stdio.h>
#include <regex>
// local includes

#include <hermes.h>
using namespace hermes;
int main(int argc, char **argv)
{
    IPAddress ip_addr = IPAddress("127.0.0.1");
    std::cout << ip_addr.GetIPAddress() << std::endl;

    const unsigned char text[100] = "hello world";

    TcpServer server = TcpServer(ip_addr);
    TcpClient client = server.Accept();
    std::regex re("^GET");
    while(1)
    {
        while(client.DataAvailable() < 3);
        std::string s = client.Receive(client.DataAvailable());
        if (std::regex_search(s, re))
        {
            std::string swk; std::cmatch m;
            std::regex_search(s.c_str(), m, std::regex("Sec-WebSocket-Key: (.*)"),
                    std::regex_constants::match_default);
            swk = m[1].str() + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

            std::cout <<  swk << std::endl; // SHA-1 and Base64 encoding of this
            uint8_t md[SHA_DIGEST_LENGTH];
            sha1((void *)swk.c_str(), swk.length(), md);

        }
    }
}