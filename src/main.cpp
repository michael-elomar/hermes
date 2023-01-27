#include <stdio.h>

// local includes

#include "../include/hermes.h"
using namespace hermes;
int main(int argc, char **argv)
{
    uint8_t ip_address[4] = {192,168,1,1};
    IPAddress ip_addr = IPAddress(ip_address, 4);

    std::cout << ip_addr.GetIPAddress() << std::endl;
}
