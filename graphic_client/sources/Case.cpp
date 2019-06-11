/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Case.hpp"

Case::Case(srv_tile_content_t *tileset, SDL_Surface *screen, srv_map_size_t *map)
{
    _tile = tileset;
    _x = tileset->x;
    _y = tileset->y;
    _back = IMG_Load("resources/Item_700.png");

    _pos.x = (screen->w / 2 - (map->x / 2)) +
        (tileset->x - tileset->y) * (_back->w / 2) - 0;
    _pos.y = (screen->h / 2 - (map->y / 2)) +
        (tileset->x + tileset->y) * (_back->h / 2) - 0;

    SDL_BlitSurface(_back, NULL, screen, &_pos);
    /*récupération de données et affichage du background de la case*/
}

Case::~Case()
{}

void Case::setTile(srv_tile_content_t *tile)
{
    _tile = tile;
}

void Case::draw()
{
    std::vector<Animation>::iterator it;

    //for (; it != _resources.end(); it++)
    //    *it->draw();
    /*Affichage de chaque ressource sur une case*/
}

void Case::AddComponent(RESOURCE_NUMBER number, int value)
{
    switch (number) {
        case 0:
            _tile->q0 += value;
            break;
        case 1:
            _tile->q1 += value;
            break;
        case 2:
            _tile->q2 += value;
            break;
        case 3:
            _tile->q3 += value;
            break;
        case 4:
            _tile->q4 += value;
            break;
        case 5:
            _tile->q5 += value;
            break;
        case 6:
            _tile->q6 += value;
            break;
    }
    /*Gestion des ressources sur une case*/
}
