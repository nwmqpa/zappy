/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Animation.hpp"

Animation::Animation(anim_option_t *options, SDL_Surface *screen)
{
    setAnimation(options);
    _screen = screen;
}

Animation::~Animation()
{

}

void Animation::setAnimation(anim_option_t *options)
{
    _options = options;
    image = IMG_Load(_options->path.c_str());
}

void Animation::draw(SDL_Rect *pos)
{
    SDL_Rect *rectimage;

    SDL_BlitSurface(image, rectimage, _screen, pos);
}
