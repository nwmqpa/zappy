/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <string>

class GraphicalException : public std::exception {
public:
    GraphicalException(std::string const& message,
        std::string const& component = "Unknown");

    std::string const& getComponent() const;
    const char* what() const noexcept;

protected:
    std::string _component;
    std::string _message;
};

#endif
