/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include <iostream>
#include "Tile.hpp"

Tile::Tile(std::string &IMGpath, SDL_Renderer *render)
    :scale(1)
{
    IMG = SDL_LoadBMP(IMGpath.c_str());
    if (IMG == NULL)
        throw GraphicalException("BMP loading error", "SDL_LoadBMP");
    x = IMG->w + scale;
    y = IMG->h + scale;
    tmp = SDL_CreateTextureFromSurface(render, IMG);
    if (tmp == NULL)
        throw GraphicalException("Buffering texture creation error",
                "SDL_CreateTextureFromSurface");
    texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, IMG->w, IMG->h);
    if (texture == NULL)
        throw GraphicalException("Texture creation error", "SDL_CreateTexture");
}

void Tile::setTileContent(srv_tile_content_t *newtile)
{
    tile = newtile;
}
/*
void Tile::draw(SDL_Renderer *render, SDL_Window *window)
{
    int w, h;

    SDL_GetWindowSize(window, &w, &h);
    if (map == NULL)
        throw GraphicalException("Map error", "srv_map_size");
    else if (tile == NULL)
        throw GraphicalException("Tile error", "srv_tile_content");

    pos.x = (w / 2 - ((map->x * scale) / 2) + x) +
        (tile->x - tile->y) * (IMG->w / 2);
    pos.y = (h / 2 - ((map->y * scale) / 2) + y) +
        (tile->x + tile->y) * (IMG->h / 2);
    pos.w = IMG->w;
    pos.h = IMG->h;

    if (SDL_RenderCopy(render, tmp, NULL, &pos) < 0)
        throw GraphicalException("Render copy error", "SDL_RenderCopy");
}
*/
void Tile::setX(int newX)
{
    x = newX;
}

void Tile::setY(int newY)
{
    y = newY;
}

void Tile::setScale(int newScale)
{
    scale = newScale;
}
