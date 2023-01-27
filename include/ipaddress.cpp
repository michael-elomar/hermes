#include "ipaddress.hpp"
#include <math.h>
#include <iostream>
#include <sstream>

namespace hermes
{
    uint32_t IPAddress::inet_addr(uint8_t *address_array, uint8_t size)
    {
        uint32_t ip_addr_value = 0;
        for(int i=0; i < size; i++)
        {
            // printf("%d\n%d\n", address_array[i], size-i-1);
            ip_addr_value += address_array[i] * pow((double)256, (double)(size - i - 1));
        }
        return ip_addr_value;
    }
    uint32_t IPAddress::inet_addr(std::string address)
    {
        uint32_t ip_addr_value = 0, i = 3;
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
    IPAddress::IPAddress(uint8_t *address_array, uint8_t size)
    {
        this->sock_addr.sin_family = AF_INET; //IPv4 by default
        this->sock_addr.sin_addr.s_addr = IPAddress::inet_addr(address_array, 4);
        this->sock_addr.sin_port = htons(DEFAULT_PORT);

        std::stringstream ss;
        for(int i=0;i < size - 1;i++)
        {
            ss << std::to_string(address_array[i]) << ".";
        }
        ss << std::to_string(address_array[size-1]);
        this->address_str = ss.str();
    }
    IPAddress::IPAddress(uint8_t *address_array, uint8_t size, uint32_t port)
    {
        this->sock_addr.sin_family = AF_INET; //IPv4 by default
        this->sock_addr.sin_addr.s_addr = IPAddress::inet_addr(address_array, size);
        this->sock_addr.sin_port = htons(port);
    }

    IPAddress::IPAddress(std::string address)
    {
        this->sock_addr.sin_family = AF_INET; //IPv4 by default
        this->sock_addr.sin_addr.s_addr = IPAddress::inet_addr(address);
        this->sock_addr.sin_port = htons(DEFAULT_PORT);

        this->address_str = address;
    }
    IPAddress::IPAddress(std::string address, uint32_t port)
    {
        this->sock_addr.sin_family = AF_INET; //IPv4 by default
        this->sock_addr.sin_addr.s_addr = IPAddress::inet_addr(address);
        this->sock_addr.sin_port = htons(port);
    }
    std::string IPAddress::GetIPAddress()
    {
        return this->address_str;
    }
    uint32_t IPAddress::GetPort()
    {
        return this->port;
    }
    sockaddr_in IPAddress::GetSockAddr()
    {
        return this->sock_addr;
    }

}
