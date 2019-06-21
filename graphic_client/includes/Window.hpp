/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

#include <SDL2/SDL.h>
#include "Tile.hpp"
#include "Exception.hpp"

#ifdef __SWITCH__
#   define BASEPATH "romfs:/"
#else
#   define BASEPATH "assets/"
#endif /* __SWITCH__ */

#define REALPATH(path) BASEPATH path

class Window {
    public:
        Window(std::string &name, int x = 800, int y = 600);
        ~Window() = default;

        void drawTile(std::vector<Tile *>, srv_map_size_t &);
        auto *getRender() { return renderer; }
        void clearScreen();
        void presentScreen();

    private:
        std::string &name;
        SDL_Renderer *renderer;
        SDL_Window *window;
        bool inits(Uint32 SDL = SDL_INIT_EVERYTHING, Uint32 IMG = IMG_INIT_PNG);
};

#endif
