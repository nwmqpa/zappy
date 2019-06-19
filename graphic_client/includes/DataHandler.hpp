/*
** EPITECH PROJECT, 2019
** DataHandler.hpp
** File description:
** DataHandler for the graphical client.
*/

#pragma once

#include <sys/epoll.h>
#include <iostream>

template <typename T>
class DataHandler {

typedef bool (*handler) (int sock, T &data);

public:
    /// DataHandler constructor that need a function
    DataHandler(int sock, handler func) noexcept
        : _sock(sock)
        , _fd(epoll_create1(0))
        , _handlerFunc(func)
        , _eventCount(0)
        , _events{}
    {
        if (_fd == -1) {
            std::cerr << "Error cannot create epoll socket." << std::endl;
            exit(84);
        }
        struct epoll_event ev = {};

        ev.events = EPOLLIN;
        ev.data.fd = _sock;
        if (epoll_ctl(_fd, EPOLL_CTL_ADD, _sock, &ev)) {
            std::cerr << "Error cannot add epoll sock." << std::endl;
            exit(84);
        }
    }

    /// Handler of the data.
    bool handle(T &data) noexcept {
        _eventCount = epoll_wait(_fd, _events, 5, 1);

        for (int i = 0; i < _eventCount; ++i) {
            if (_handlerFunc(_sock, data) == false) {
                cleanupSocket();
                return false;
            }
        }
        return true;
    }

private:
    void cleanupSocket() noexcept {
        struct epoll_event event = {};

        event.events = EPOLLIN;
        event.data.fd = _sock;
        if (epoll_ctl(_fd, EPOLL_CTL_DEL, _sock, &event))
            std::cerr << "Connection with the server closed.\n" << std::endl;
        close(_sock);
    }

    int _sock;
    int _fd;
    handler _handlerFunc;
    int _eventCount;
    struct epoll_event _events[5];
};
