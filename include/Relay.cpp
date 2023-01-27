#include "Relay.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

namespace hermes
{
    Relay::Relay()
    {
        int opt = 1, backlog = 5;
        printf("Beginning\n");
        this->server_fd = socket(AF_INET,SOCK_STREAM, 0);
        if(this->server_fd < 0)
        {
            printf("Socket failed\n");
            exit(EXIT_FAILURE);
        }
        // Forcefully attaching socket to the port 8080
        if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        {
            printf("Failure to perform setsockopt\n");
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        this->address.sin_family = AF_INET;
        this->address.sin_addr.s_addr = INADDR_ANY;
        this->address.sin_port = htons(PORT);
        printf("Address created successfully\n");

        if (bind(this->server_fd, (sockaddr *)&this->address, sizeof(this->address)) < 0)
        {
            printf("Bind operation failed\n");
            exit(EXIT_FAILURE);
        }
        printf("Bind successful\n");

        if (listen(this->server_fd, backlog) < 0)
        {
            printf("Listening operation failed\n");
            exit(EXIT_FAILURE);
        }
        printf("Listening successful\n");

        int addrlen = sizeof(this->address);
        if ((this->new_socket = accept(this->server_fd, (struct sockaddr*)&this->address,
                      (socklen_t*) &addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Relay instance created successfully\n");
    }
    int Relay::Shutdown()
    {
        int close_status, shutdown_status;
        close_status = close(this->new_socket);
        shutdown_status = shutdown(this->server_fd, SHUT_RDWR);
        return close_status + shutdown_status;
    }
}
