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

        void updateTile();
        srv_tile_content_t *getTile() {return tile;}
        void draw(SDL_Renderer *, SDL_Window *);

        void setTileContent(srv_tile_content_t *);
        void setMapSize(srv_map_size_t *);

        void setX(int);
        void setY(int);
        void setScale(int);
        int getX() { return x; }
        int getY() { return y; }
        int getScale() { return scale; }
        srv_map_size_t *getMap() { return map; }

    private:
        SDL_Surface *IMG;
        SDL_Texture *texture;
        SDL_Texture *tmp;

        SDL_Rect pos;
        srv_tile_content_t *tile;
        srv_map_size_t *map;

        int scale;
        int x;
        int y;
};
#endif
