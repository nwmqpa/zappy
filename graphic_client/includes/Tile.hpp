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
    
    bool hasFood() const { return this->tile->q0 > 0; }
    bool hasLinemate() const { return this->tile->q1 > 0; }
    bool hasDeraumere() const { return this->tile->q2 > 0; }
    bool hasSibur() const { return this->tile->q3 > 0; }
    bool hasMendiane() const { return this->tile->q4 > 0; }
    bool hasPhyras() const { return this->tile->q5 > 0; }
    bool hasThystame() const { return this->tile->q6 > 0; }

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
