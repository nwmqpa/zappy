/*
** EPITECH PROJECT, 2019
** socket.h
** File description:
** Socket abstraction library inspired by Rust std::net::Tcp~
*/

#ifndef TCP_LIB_H_
#define TCP_LIB_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

typedef int (*disp_func)(int fd, void *data);

/*
* Dispatcher structure that handle function for sockets.
*
*/
typedef struct dispatcher_s {
    int listener;
    fd_set actives;
    disp_func on_active;
    disp_func on_connect;
    disp_func on_delete;
} dispatcher_t;

/*
* Take a dispatcher a listener and a function and dispatch the function to
* all active sockets. (Work with `select` under the hood.)
*/
int dispatch(dispatcher_t *this, void *data);

#endif /* TCP_LIB_H_ */
