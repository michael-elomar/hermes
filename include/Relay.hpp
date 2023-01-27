#ifndef RELAY_HPP
#define RELAY_HPP

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


namespace hermes
{
    class Relay
    {
        public:
            Relay();
            int Shutdown();
            void Read(char *buf);
        private:
            int server_fd, new_socket, valread;
            struct sockaddr_in address;
            char *buffer;


    };
}
#endif // RELAY_HPP
