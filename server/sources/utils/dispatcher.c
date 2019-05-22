/*
** EPITECH PROJECT, 2019
** dispatcher.c
** File description:
** dispatcher
*/

#include "dispatcher.h"

static void cleanup_socket(fd_set *actives, int socket)
{
    close(socket);
    FD_CLR(socket, actives);
}

static int setup_fd(dispatcher_t *this, int socket, void *data)
{
    if (socket < 0) {
        return -1;
    } else {
        this->on_connect(socket, data);
        FD_SET(socket, &this->actives);
    }
    return 0;
}

int dispatch(dispatcher_t *this, void *data)
{
    unsigned int size = sizeof(struct sockaddr);
    struct sockaddr_in stream_addr = {0};
    fd_set read_fd_set = this->actives;

    FD_ZERO(&this->actives);
    FD_SET(this->listener, &this->actives);
    if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
        perror("select");
        return -1;
    }
    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (!FD_ISSET(i, &read_fd_set))
            continue;
        (void) data;
        if (i == this->listener)
            setup_fd(this, accept(i, (struct sockaddr *) &stream_addr, &size),
                    data);
        else if (this->on_active(i, data) < 0) {
            this->on_delete(i, data);
            cleanup_socket(&this->actives, i);
        }
    }
    return 0;
}
