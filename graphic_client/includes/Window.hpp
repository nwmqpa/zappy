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
#include "GameState.hpp"

#ifdef __SWITCH__
#   define BASEPATH "romfs:/"
#else
#   define BASEPATH "assets/"
#endif /* __SWITCH__ */

#define REALPATH(path) BASEPATH path

class Window {
    public:
        class Isometry {
            public:
                Isometry() = default;
                ~Isometry() = default;

                static float setPositionX(float, float, float, float, float, Camera);
                static float setPositionY(float, float, float, float, float, Camera);
                static float setWidth(float, Camera);
                static float setHeight(float, Camera);
        };

        Window(std::string &name, int x = 800, int y = 600);
        ~Window();

        void render(GameState &state, int, int);
        //void addY(int, std::vector<Tile *>);
        //void addX(int, std::vector<Tile *>);

        //int getY() { return y; }
        //int getX() { return x; }

        void move(float, float);
        void setCameraSize(int, int);

        void clearScreen();
        void presentScreen();

        auto *getRender() { return renderer; }
    private:
        std::string &name;
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Rect camera;

        //int x;
        //int y;
        bool initSDL(Uint32 SDL = SDL_INIT_EVERYTHING);
};

#endif
