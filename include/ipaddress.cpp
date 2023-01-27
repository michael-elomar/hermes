#include "ipaddress.hpp"
#include <math.h>
#include <iostream>
#include <sstream>

namespace hermes
{
    in_addr_t IPAddress::inet_addr(std::string address)
    {
        in_addr_t ip_addr_value = 0, i = 3;
        std::string delimiter = ".";
        while (address.find(delimiter) != std::string::npos) {
            std::string token = address.substr(0, address.find(delimiter));
            ip_addr_value += std::stoi(token) * pow(256, i);
            address.erase(0, address.find(delimiter) + delimiter.length());
            i--;
        }
        ip_addr_value += std::stoi(address) * pow(256, i);
        return ip_addr_value;
    }
    IPAddress::IPAddress() {}

    IPAddress::IPAddress(std::string address)
    {
        this->sock_addr.sin_family = AF_INET; //IPv4 by default
        this->sock_addr.sin_addr.s_addr = htonl(IPAddress::inet_addr(address));
        this->sock_addr.sin_port = htons(DEFAULT_PORT);

        this->address_str = address;
        this->port = DEFAULT_PORT;
    }
    IPAddress::IPAddress(std::string address, uint32_t port)
    {
        this->sock_addr.sin_family = AF_INET; //IPv4 by default
        this->sock_addr.sin_addr.s_addr = htonl(IPAddress::inet_addr(address));
        this->sock_addr.sin_port = htons(port);

        this->address_str = address;
        this->port = port;
    }
    std::string IPAddress::GetIPAddress()
    {
        return this->address_str;
    }
    uint32_t IPAddress::GetPort()
    {
        return this->port;
    }
    struct sockaddr* IPAddress::GetSockAddr()
    {
        return (struct sockaddr *) &(this->sock_addr);
    }
    socklen_t IPAddress::GetSockAddrLen()
    {
        return sizeof(this->sock_addr);
    }

}
