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
        Case(srv_tile_content_t *, srv_map_size_t *);
        ~Case();

        void setTile(srv_tile_content_t *);
        srv_tile_content_t *getTile() {return tile;}
        void draw(SDL_Surface *);

    private:
        SDL_Surface *back;
        SDL_Rect pos;
        srv_tile_content_t *tile;
        srv_map_size_t *map;

        int x;
        int y;
};

#endif
