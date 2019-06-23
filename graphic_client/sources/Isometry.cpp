/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Window.hpp"

float Window::Isometry::getIsoX(int cartX, int cartY, float surfaceWidth, float surfaceHeight, float screenWidth, float screenHeight, Camera camera)
{
    float ret = ((cartX * surfaceWidth) - (cartY * surfaceWidth)) / 2;
    ret += (screenWidth / 2) - (surfaceWidth / 2);
    ret /= camera.scale.x;
    ret += camera.center.x;
    return ret;
}

float Window::Isometry::getIsoY(int cartX, int cartY, float surfaceWidth, float surfaceHeight, float screenWidth, float screenHeight, Camera camera)
{
    float ret = ((cartX * surfaceHeight) + (cartY * surfaceHeight)) / 4;
    ret += (screenHeight / 2) - (surfaceHeight / 2) * (screenHeight / 2);
    ret /= camera.scale.y;
    ret += camera.center.y;
    return ret;
}

float Window::Isometry::getIsoWidth(float value, Camera camera)
{
    return (value / camera.scale.x);
}

float Window::Isometry::getIsoHeight(float value, Camera camera)
{
    return (value / camera.scale.y);
}
