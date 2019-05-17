/*
** EPITECH PROJECT, 2019
** server_init.c
** File description:
** server intializers functions.
*/

#include "logger.h"
#include "server.h"

static void fill_addr(short port, struct sockaddr_in *addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = INADDR_ANY;
}

static int create_socket(struct sockaddr *addr)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        errorl("socket: %s\n", strerror(errno));
        return -1;
    }
    if (bind(sock, addr, sizeof(struct sockaddr)) == -1) {
        errorl("bind: %s\n", strerror(errno));
        return -1;
    }
    if (listen(sock, 0) == -1) {
        errorl("listen: %s\n", strerror(errno));
        return -1;
    }
    return sock;
}

int create_client_listener(options_t *options)
{
    struct sockaddr addr = {0};

    fill_addr(options->port, (struct sockaddr_in *) &addr);
    return create_socket(&addr);
}

int create_graphic_listener(options_t *options)
{
    struct sockaddr addr = {0};

    fill_addr(options->port + 1, (struct sockaddr_in *) &addr);
    return create_socket(&addr);
}
