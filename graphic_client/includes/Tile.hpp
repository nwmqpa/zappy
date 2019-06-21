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

        void setTileContent(srv_tile_content_t *);
        srv_tile_content_t *getTileInfo() { return tile; }

        void setX(int);
        void setY(int);
        void setScale(int);

        int getX() { return x; }
        int getY() { return y; }
        int getScale();

        SDL_Surface *getSurface() { return IMG; }
        SDL_Texture *getTmp() { return tmp; }

        int getPosX() { return tile->x; }
        int getPosY() { return tile->y; }

    private:
        SDL_Surface *IMG;
        SDL_Texture *texture;
        SDL_Texture *tmp;

        srv_tile_content_t *tile;

        int scale;
        int x;
        int y;
};
#endif
