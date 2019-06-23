/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef TILE_HPP_
#define TILE_HPP_

#include "protocols.h"
#include "Animation.hpp"
#include "Exception.hpp"
#include <SDL2/SDL.h>
#include <vector>

class Tile {
public:
    Tile(SDL_Texture *texture, int height, int width);
    ~Tile() = default;

    void setTileContent(int, int, std::vector<int>, int);

    srv_tile_content_t* getTileInfo() { return tile; }
    SDL_Texture *getTexture() const { return texture; }

    int getPosX() { return tile->x; }
    int getPosY() { return tile->y; }
    int getHeight() const noexcept { return height; }
    int getWidth() const noexcept { return width; }

    SDL_Rect getArea() { return area; }
    void setArea(SDL_Rect area);

private:
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect area;
    srv_tile_content_t *tile;
    float height;
    float width;
};
#endif
