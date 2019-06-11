/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical client
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

#include <vector>
#include "protocols.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "Case.hpp"

class Map {
    public:
        Map();
        ~Map();

        void getSize();
        void generateMap();
        void getMapsrv();
    private:
        std::vector<Case *> _map;
        srv_map_size_t *_map_size;
};

#endif
