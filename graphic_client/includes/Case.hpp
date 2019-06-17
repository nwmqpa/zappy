/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

#include "Animation.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "protocols.h"
#include <vector>

class Tile {
    public:
        Tile(srv_tile_content_t *, srv_map_size_t *, std::string, SDL_Renderer *);
        ~Tile();

        void updateTile();
        srv_tile_content_t *getTile() {return tile;}
        void draw(SDL_Renderer *, SDL_Window *);

        void setPosX(int value) {posx = value;}
        void setPosY(int value) {posy = value;}
        void setScale(int value) {scale = value;}
        int getPosX() {return posx;}
        int getPosY() {return posy;}
        int getScale() {return scale;}


    private:
        SDL_Surface *IMG;
        SDL_Texture *texture;
        SDL_Texture *tmp;

        SDL_Rect pos;
        srv_tile_content_t *tile;
        srv_map_size_t *map;

        int scale;
        int posx;
        int posy;
        int x;
        int y;
};

#endif
