#ifndef IPADDRESS_HPP
#define IPADDRESS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <netinet/in.h>
#include <iostream>

#define DEFAULT_PORT 8080

namespace hermes
{
    class IPAddress
    {
        public:
            IPAddress(uint8_t *address, uint8_t size);
            IPAddress(uint8_t *address, uint8_t size, uint32_t port);

            IPAddress(std::string address);
            IPAddress(std::string address, uint32_t port);

            static uint32_t inet_addr(std::string address);
            static uint32_t inet_addr(uint8_t *address, uint8_t size);

            std::string GetIPAddress() const;
            uint32_t GetPort() const;
            sockaddr_in GetSockAddr() const;





        private:
            sockaddr_in sock_addr;
            uint32_t port;
            std::string address_str;
    };
}
#endif // IPADDRESS_HPP
