/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Exception.hpp"

GraphicalException::GraphicalException(std::string const& message,
    std::string const& component)
{
    _message = message;
    _component = component;
}

std::string const& GraphicalException::getComponent() const
{
    return _component;
}

const char* GraphicalException::what() const noexcept
{
    return _message.c_str();
}
