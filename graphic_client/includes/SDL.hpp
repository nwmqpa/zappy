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

        bool inits(Uint32 SDL = SDL_INIT_EVERYTHING, Uint32 IMG = IMG_INIT_PNG);

        void life();

        void update();
        void server_event();
        void client_event();

        void addX(int);
        void addY(int);
        void scale(int);

        void updateTileList(std::vector<Tile *>value) {tileList = value;}

        void drawTile();

        void destroy();

        SDL_Renderer *getRender() {return renderer;}
    private:
        bool heart;

        std::vector<Tile *>tileList;
        const char *name;
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Event event;
};

#endif
