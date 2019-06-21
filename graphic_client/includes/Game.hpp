/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

#include "GameState.hpp"
#include "Window.hpp"

typedef void (*data_processor_t)(GameState &, Window &);

class Game {
    public:
        Game(std::string &ip, int port);
        ~Game() = default;

        void life(Window &);
        void processData(Window &);
        void eventLoop(Window &, std::vector<Tile *>);

    private:
        std::string ip;
        int port;
        GameState state;
};

#endif
