/*
** EPITECH PROJECT, 2019
** DataHandler.hpp
** File description:
** DataHandler for the graphical client.
*/

#pragma once

#include <iostream>
#include <unistd.h>
#include <fcntl.h>

template <typename T>
class DataHandler {

typedef bool (*handler) (int sock, T &data);

public:
    /// DataHandler constructor that need a function
    DataHandler(int sock, handler func) noexcept
        : _sock(sock)
        , _handlerFunc(func)
    {
        int flags = fcntl(sock, F_GETFL, 0);

        fcntl(sock, F_SETFL, flags | O_NONBLOCK);
    }

    bool handle(T &data) noexcept
    {
        if (_handlerFunc(_sock, data) == false) {
            cleanupSocket();
            return false;
        }
        return true;
    }

private:
    void cleanupSocket() noexcept
    {
        close(_sock);
    }

    int _sock;
    handler _handlerFunc;
};
