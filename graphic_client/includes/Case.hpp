/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef CASE_HPP_
    #define CASE_HPP_

#include "SDL2/SDL.h"
#include "protocols.h"

class Case {
    public:
        Case();
        ~Case();

        void draw();
        void addComponent(RESOURCE_NUMBER id, int value);

    private:
        SDL_Surface *_back;
        srv_tile_content_t *tile;
        int _x;
        int _y;
        std::vector<animation> _resources;
};

#endif
