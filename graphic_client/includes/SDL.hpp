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

class WindowCreator {
    public:
        WindowCreator(const char *name = "Zappy", int x = 800, int y = 600, Uint32 flags = SDL_WINDOW_RESIZABLE);
        ~WindowCreator();

        bool Inits(Uint32 SDL = SDL_INIT_VIDEO, Uint32 IMG = IMG_INIT_PNG);
        //Initialisation IMG et SDL

        void Life();
        bool Update();

        void Destroy();

        SDL_Surface *screen;
    private:
        bool heart;

        SDL_Window *window;
        SDL_Event event;
};

#endif
