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

typedef void (*handler) (T &data);

public:
    /// DataHandler constructor that need a function
    DataHandler(int sock, handler func) noexcept
        : _sock(sock)
        , _fd(epoll_create1(0))
        , _handlerFunc(func)
        , _eventCount(0)
        , _events{0, 0, 0, 0, 0}
    {
        if (_fd == -1) {
            std::cerr << "Error cannot create epoll." << std::endl;
            exit(84);
        }
    }

    /// Handler of the data.
    void handle(T &data) noexcept {
        _eventCount = epoll_wait(_fd, _events, 5, 1);

        for (int i = 0; i < _eventCount; ++i) {
            if (_events[i].data.fd == _sock) {
                _handlerFunc(data);
            }
        }
    }

private:
    int _sock;
    int _fd;
    handler _handlerFunc;
    int _eventCount;
    struct epoll_event _events[5];
};
