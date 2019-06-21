/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

#include "Exception.hpp"
#include "Animation.hpp"
#include "SDL2/SDL.h"
#include "protocols.h"
#include <vector>

class Tile {
    public:
        Tile(std::string &, SDL_Renderer *);
        ~Tile() = default;

        void setTileContent(int, int, std::vector<int>, int);

        srv_tile_content_t *getTileInfo() { return tile; }
        SDL_Surface *getSurface() { return img; }
        SDL_Texture *getTmp() { return tmp; }

        int getPosX() { return tile->x; }
        int getPosY() { return tile->y; }

    private:
        SDL_Surface *img;
        SDL_Texture *texture;
        SDL_Texture *tmp;

        srv_tile_content_t *tile;
};
#endif
