/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include <iostream>
#include "Case.hpp"

Tile::Tile(srv_tile_content_t *tileSet, srv_map_size_t *mapData,
        std::string IMGpath, SDL_Renderer *render)
{
    tile = tileSet;
    map = mapData;

    scale = 1;
    x = tileSet->x;
    y = tileSet->y;
    IMG = SDL_LoadBMP(IMGpath.c_str());
    if (IMG == NULL)
        printf("Error PathImage");
    posx = IMG->w + scale;
    posy = IMG->h + scale;
    tmp = SDL_CreateTextureFromSurface(render, IMG);
    if (tmp == NULL)
        printf("TMP error\n");
    texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, IMG->w, IMG->h);
}

Tile::~Tile()
{
}

void Tile::updateTile()
{
    //requête API
    //tile = result;
}

void Tile::draw(SDL_Renderer *render, SDL_Window *window)
{
    int w, h;

    SDL_GetWindowSize(window, &w, &h);
    pos.x = (w / 2 - ((map->x * scale) / 2) + posx) +
        (tile->x - tile->y) * (IMG->w / 2);
    pos.y = (h / 2 - ((map->y * scale) / 2) + posy) +
        (tile->x + tile->y) * (IMG->h / 2);
    pos.w = IMG->w * 3;
    pos.h = IMG->h * 3;

    if (SDL_RenderCopy(render, tmp, NULL, &pos) < 0)
        printf("Print Error:%s\n", SDL_GetError());
}
