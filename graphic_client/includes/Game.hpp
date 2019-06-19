/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef GAME_HPP_
    #define GAME_HPP_

#include "protocols.h"
#include "Protocol.hpp"
#include "DataHandler.hpp"
#include <errno.h>

struct srv_game_data {
    int id;

    srv_map_size_t mapSize;
    srv_tile_content_t tileContent;
};

typedef struct srv_game_data srv_game_data_t;

class Game {
    public:
        Game(int, const char *);
        ~Game() = default;

        void Life(WindowCreator *);
    private:
        int port;
        const char *ip;
        srv_game_data_t data;
};

#endif
