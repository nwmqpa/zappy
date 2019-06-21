/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Window.hpp"

float Window::Isometry::setPositionX(float width, float map, float tileX, float tileY, float surface, float camera)
{
    return ((width / 2 - (map / 2)) + (tileX - tileY) * (surface / 2) - (surface / 2) + camera);
}

float Window::Isometry::setPositionY(float height, float map, float tileX, float tileY, float surface, float camera)
{
    return ((height / 2 - (map / 2)) + (tileX + tileY) * (surface / 2) - ((surface + tileY) * 64) - (map / 2 * surface) + camera);
}

float Window::Isometry::setWidth(float value)
{
    return (value / 4);
}

float Window::Isometry::setHeight(float value)
{
    return (value / 4);
}
