/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#ifndef WINDOWCREATOR_HPP_
    #define WINDOWCREATOR_HPP_

#include <SDL2/SDL.h>

#include "Tile.hpp"
#include "Exception.hpp"

#ifdef __SWITCH__
#   define BASEPATH "romfs:/"
#else
#   define BASEPATH "assets/"
#endif /* __SWITCH__ */

#define REALPATH(path) BASEPATH path

class WindowCreator {
    public:
        WindowCreator(std::string &name, int x = 800, int y = 600);
        ~WindowCreator() = default;

        bool inits(Uint32 SDL = SDL_INIT_EVERYTHING, Uint32 IMG = IMG_INIT_PNG);

        void life();

        void update();
        void server_event();
        void client_event();

        void addX(int);
        void addY(int);
        void scale(int);

        void drawTile();
        void destroy();

        auto *getRender() { return renderer; }
        auto *getWindow() { return window; }
        bool getHeart() { return heart; }

    private:
        bool heart;

        std::vector<Tile *>tileList;
        std::string &name;
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Event event;
};

#endif
