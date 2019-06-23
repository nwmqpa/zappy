/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"

Egg::Egg(unsigned int num, int x, int y, SDL_Texture *texture, int width, int height)
 : texture(texture)
 , eggNum(num)
 , x(x)
 , y(y)
 , width(width)
 , height(height)
{
}
