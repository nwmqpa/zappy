/*
** EPITECH PROJECT, 2019
** server.h
** File description:
** server header file.
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include "options.h"
#include "generic_list.h"

typedef struct server_s {
    int listener_client;
    int listener_graphic;
    unsigned int width;
    unsigned int height;
    char **teams;
    list_t *clients;
} server_t;

// Create server and initiliaze it from options.
server_t *create_server(options_t *options);

int create_client_listener(options_t *options);
int create_graphic_listener(options_t *options);

void print_server(server_t *server);

/*
** Client commands.
*/
char *connect_nbr(const server_t *server);

#endif /* SERVER_H_ */
