/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

#include "GameState.hpp"
#include "WindowCreator.hpp"

typedef void (*data_processor_t)(GameState &, WindowCreator &);

class Game {
    public:
        Game(std::string &ip, int port);
        ~Game() = default;

        void life(WindowCreator &);
        void processData(WindowCreator &);
        void eventLoop(WindowCreator &);

    private:
        std::string ip;
        int port;
        GameState state;
};

#endif
