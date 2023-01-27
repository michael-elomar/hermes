#ifndef IPADDRESS_HPP
#define IPADDRESS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <netinet/in.h>
#include <iostream>

#define DEFAULT_PORT 56789

namespace hermes
{
    class IPAddress
    {
        public:
            IPAddress();

            IPAddress(std::string address);
            IPAddress(std::string address, uint32_t port);

            static in_addr_t inet_addr(std::string address);

            std::string GetIPAddress();
            uint32_t GetPort();
            struct sockaddr_in GetSockAddr();

        private:
            struct sockaddr_in sock_addr;
            uint32_t port;
            std::string address_str;
    };
}
#endif // IPADDRESS_HPP
