/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Tile.hpp"
#include <SDL2/SDL.h>
#include <iostream>

Tile::Tile(SDL_Texture *texture, int height, int width)
    : texture(texture)
    , area()
    , tile(nullptr)
    , height(height)
    , width(width)
{
}

void Tile::setTileContent(int x, int y, std::vector<int> inventory, int nbplayer)
{
    if (tile == nullptr)
        tile = new srv_tile_content_t;
    tile->x = x;
    tile->y = y;
    tile->q0 = inventory.at(0);
    tile->q1 = inventory.at(1);
    tile->q2 = inventory.at(2);
    tile->q3 = inventory.at(3);
    tile->q4 = inventory.at(4);
    tile->q5 = inventory.at(5);
    tile->q6 = inventory.at(6);
    tile->players = nbplayer;
}

void Tile::setArea(SDL_Rect area)
{
    this->area = area;
}
