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

        bool inits(Uint32 SDL = SDL_INIT_EVERYTHING, Uint32 IMG = IMG_INIT_PNG);

        void addY(int, std::vector<Tile *>);
        void addX(int, std::vector<Tile *>);

        int getY() { return y; }
        int getX() { return x; }

        void drawTile(std::vector<Tile *>, srv_map_size_t &);
        auto *getRender() { return renderer; }
        void clearScreen();
        void PresentScreen();
        void destroyer();

    private:
        std::string &name;
        SDL_Renderer *renderer;
        SDL_Window *window;

        float x;
        float y;
};

#endif
