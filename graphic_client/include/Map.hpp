/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical client
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

#include <vector>
#include "protocols.hpp"
#include "SDL2/SDL_image.h"

class Map {
    public:
        Map();
        ~Map();

        bool getTile();
        bool getSize();
        bool generateMap();
        void mainCycle();

        bool getLife();
        bool setLife();

    private:
        SDL_Window *_window;
        SDL_Surface *_screen;
        SDL_Event *_event;

        bool _isAlive;
        std::vector<Case *> _map;

        srv_map_size_t *_map_size;
};

#endif
