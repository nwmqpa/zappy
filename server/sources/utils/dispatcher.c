/*
** EPITECH PROJECT, 2019
** dispatcher.c
** File description:
** dispatcher
*/

#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include "dispatcher.h"
#include "logger.h"

static void cleanup_socket(dispatcher_t *this, int socket)
{
    struct epoll_event event = {0};
    
    event.events = EPOLLIN;
    event.data.fd = socket;
    if (epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, socket, &event))
        errorl("Failed to remove file descriptor to epoll\n");
    close(socket);
}

static int setup_fd(dispatcher_t *this, int socket, void *data)
{
    struct epoll_event event = {0};
    
    event.events = EPOLLIN;
    event.data.fd = socket;
    if (socket < 0) {
        return -1;
    } else {
        if (epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, socket, &event)) {
            errorl("Failed to add file descriptor to epoll\n");
            close(socket);
            return 1;
        }
        this->on_connect(socket, data);
    }
    return 0;
}

int dispatch(dispatcher_t *this, void *data)
{
    unsigned int size = sizeof(struct sockaddr);
    struct sockaddr_in saddr = {0};
    struct epoll_event events[5];
    int event_count = epoll_wait(this->epoll_fd, events, 5, 1);

    for (int i = 0; i < event_count; i++) {
        if (events[i].data.fd == this->main_socket) {
            setup_fd(this,
            accept(events[i].data.fd, (struct sockaddr *) &saddr, &size),
            data);
        } else if (this->on_active(events[i].data.fd, data) < 0) {
            this->on_delete(events[i].data.fd, data);
            cleanup_socket(this, events[i].data.fd);
        }
    }
    return 0;
}
