/*
** EPITECH PROJECT, 2019
** Protocol.hpp
** File description:
** Protocol header.
*/

#pragma once


#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <netdb.h>
#include <string>
#include "protocols.h"

/// The protocol just ask for something but it's not blocking.
/// The response will be handled when it is ready in the dispatcher.
class Protocol {
public:
    /// Protocol constructor that need a port to connect.
    Protocol(std::string ip, short int port);

    /// Removing assignement operator.
    void operator=(Protocol lhs) = delete;
    /// Removing default constructor.
    Protocol() = delete;

    /// Return a copy of the socket.
    int getSocket() const noexcept;

    bool askMapSize() const noexcept;

    bool askTileContent(unsigned int x, unsigned int y) const noexcept;

    bool askMapContent() const noexcept;

    bool askTeamsNames() const noexcept;

    bool askPlayerPosition(unsigned int id) const noexcept;

    bool askPlayerLevel(unsigned int id) const noexcept;

    bool askPlayerInventory(unsigned int id) const noexcept;

    bool askTimeUnitRequest() const noexcept;

    bool askTimeUnitChange() const noexcept;

    int setupSocket();

private:
    /// The port in little endian.
    short int _port;
    /// The ip stored in string.
    std::string _ip;
    /// The socket to the server.
    int _sock;
};
