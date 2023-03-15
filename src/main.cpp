#include <stdio.h>
#include <regex>
#include <math.h>
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
            char *sha1Base64 = base64Encode(md, SHA_DIGEST_LENGTH);

            std::stringstream response;
            response << "HTTP/1.1 101 Switching Protocols\r\n";
            response << "Connection: Upgrade\r\n";
            response << "Upgrade: websocket\r\n";
            response << "Sec-WebSocket-Accept: " << sha1Base64  << "\r\n\r\n";
            client.Send(response.str());
        }
        else
        {
            unsigned char *bytes = (unsigned char *)s.c_str();
            bool fin = (bytes[0] & 0b10000000) != 0;
            int opcode = bytes[0] & 0b00001111;
            bool mask = (bytes[1] & 0b10000000) != 0;
            int offset = 2;
            uint64_t msglen = bytes[1] & 0b01111111;
            if (msglen == 126)
            {
                msglen = bytes[3] + bytes[2] * 0x100;
                offset = 4;
            }
            else if (msglen >= 127)
            {
                for (int i = 2; i < 10 ; i++)
                {
                    msglen += bytes[-i+11] * (0x1 * pow(16, 2*i-2));
                }
                offset = 10;
            }
            if (msglen == 0)
            {
                std::cout << "msglen == 0";
            }
            else if(mask)
            {
                uint8_t *decoded = (uint8_t *)malloc(msglen);
                uint8_t masks[4] = {bytes[offset], bytes[offset+1], bytes[offset+2], bytes[offset+3]};
                offset +=4;

                for (uint64_t i = 0;i < msglen; ++i)
                {
                    decoded[i] = (uint8_t)(bytes[offset + i] ^ masks[i % 4]);
                }
                std::string string;
                string.assign((char *)decoded);
                std::cout << string << std::endl;
            }
            else
                std::cout << "Mask bit not set\n";
            std::cout << std::endl;
        }
    }
}