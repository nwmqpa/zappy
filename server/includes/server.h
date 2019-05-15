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

typedef struct server_s {
    int listener_client;
    int listener_graphic;
    char **teams;
} server_t;

int create_listener(options_t *options);
server_t *setup_server(options_t *options);

#endif /* SERVER_H_ */
