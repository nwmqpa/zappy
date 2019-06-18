/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef ANIMATIONS_HPP_
    #define ANIMATIONS_HPP_

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct anim_option_s {
    std::string path;
    int picture_in_line;
    int maxpicture;
    int lines;
};
typedef struct anim_option_s anim_option_t;

class Animation {
    public:
        Animation(anim_option_t *, SDL_Surface *);
        ~Animation();

        void setAnimation(anim_option_t *);
        void draw(SDL_Rect *);
    private:
        anim_option_t *_options;
        SDL_Surface *image;
        SDL_Surface *_screen;
};

#endif
