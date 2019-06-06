/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef CASE_HPP_
    #define CASE_HPP_

#include "Animation.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "protocols.h"
#include <vector>

class Case {
    public:
        Case(srv_tile_content_t *, SDL_Surface *);
        ~Case();

        void draw();
        void AddComponent(RESOURCE_NUMBER id, int value);

    private:
        SDL_Surface *_back;
        srv_tile_content_t *_tile;
        int _x;
        int _y;
        std::vector<Animation> _resources;
};

#endif
