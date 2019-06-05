/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Case.hpp"

Case::Case(srv_tile_content_t *tileset)
{
    _tile = tileset;
    _x = tileset.x;
    _y = tileset.y;
    _back = ;

}

Case::~Case()
{}

void Case::draw()
{
    std::vector<animation>::iterator it;

    for (; it != _resources.end(); it++)
        *it->draw();
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
}
