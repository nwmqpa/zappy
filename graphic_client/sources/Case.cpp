/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Case.hpp"

Case::Case(srv_tile_content_t *tileSet, srv_map_size_t *mapData)
{
    tile = tileSet;
    map = mapData;
    x = tileSet->x;
    y = tileSet->y;
    back = IMG_Load("resources/Item_700.png");

    /*récupération de données et affichage du background de la case*/
}

Case::~Case()
{}

void Case::setTile(srv_tile_content_t *newTile)
{
    tile = newTile;
}

void Case::draw(SDL_Surface *screen)
{
    pos.x = (screen->w / 2 - (map->x / 2)) +
        (tile->x - tile->y) * (back->w / 2) - 0;
    pos.y = (screen->h / 2 - (map->y / 2)) +
        (tile->x + tile->y) * (back->h / 2) - 0;
    SDL_BlitSurface(back,
                    NULL,
                    screen,
                    &pos);
    //std::vector<Animation>::iterator it;

    //for (; it != _resources.end(); it++)
    //    *it->draw();
    /*Affichage de chaque ressource sur une case*/
}
