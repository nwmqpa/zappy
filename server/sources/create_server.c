/*
** EPITECH PROJECT, 2019
** create_server.c
** File description:
** Create socket for the server.
*/

#include "server.h"
#include "logger.h"

static int fill_addr(short port, struct sockaddr_in *addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = INADDR_ANY;
}

int create_listener(options_t *options)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr addr = {0};

    if (sock != -1) {
        errorl("socket: %s\n", strerror(errno));
        exit(84);
    }
    fill_addr(options->port, (struct sockaddr_in *) &addr);
    if (bind(sock, &addr, sizeof(struct sockaddr)) == -1) {
        errorl("bind: %s\n", strerror(errno));
        exit(84);
    }
    if (listen(sock, 0) == -1) {
        errorl("listen: %s\n", strerror(errno));
        exit(84);
    }
    return sock;
}

int setup_server(options_t *options)
{
    return 0;
}
