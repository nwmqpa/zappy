/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include <iostream>
#include "Tile.hpp"

Tile::Tile(std::string &imgpath, SDL_Renderer *render)
 : tile(nullptr)
{
    img = SDL_LoadBMP(imgpath.c_str());
    if (img == nullptr)
        throw GraphicalException("BMP loading error", "SDL_LoadBMP");
    tmp = SDL_CreateTextureFromSurface(render, img);
    if (tmp == nullptr)
        throw GraphicalException("Buffering texture creation error",
                "SDL_CreateTextureFromSurface");
    texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, img->w, img->h);
    if (texture == nullptr)
        throw GraphicalException("Texture creation error", "SDL_CreateTexture");
}

void Tile::setTileContent(int x, int y, std::vector<int> inventory, int nbplayer)
{
    tile = new srv_tile_content_t;
    std::cout << x << ", " << y << std::endl;
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
