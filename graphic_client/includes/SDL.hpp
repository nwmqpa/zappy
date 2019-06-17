/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#ifndef WINDOWCREATOR_HPP_
    #define WINDOWCREATOR_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Case.hpp"

class WindowCreator {
    public:
        WindowCreator(const char *name = "Zappy", int x = 800, int y = 600);
        ~WindowCreator();

        bool Inits(Uint32 SDL = SDL_INIT_VIDEO, Uint32 IMG = IMG_INIT_PNG);

        void Life(std::vector<Case>);
        bool Update();

        void Destroy();


        SDL_Surface *GetWindow() {return screen;}
    private:
        bool heart;

        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Surface *screen;
        SDL_Event event;
};

#endif
