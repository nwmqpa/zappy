/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "Exception.hpp"
#include "GameState.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include <SDL2/SDL.h>

#ifdef __SWITCH__
#define BASEPATH "romfs:/"
#else
#define BASEPATH "assets/"
#endif /* __SWITCH__ */

#define REALPATH(path) BASEPATH path

class Window {
public:
    class Isometry {
    public:
        Isometry() = default;
        ~Isometry() = default;

        static float getIsoX(int cartX, int cartY, float surfaceWidth, float surfaceHeight, float screenWidth, float screenHeight, Camera camera);
        static float getIsoY(int cartX, int cartY, float surfaceWidth, float surfaceHeight, float screenWidth, float screenHeight, float mapHeight, Camera camera);
        static float getIsoWidth(float surfaceWidth, Camera);
        static float getIsoHeight(float surfaceHeight, Camera);
    };

    Window(std::string& name, int x = 800, int y = 600);
    ~Window();

    void render(GameState& state, int, int);

    void move(float, float);
    void setCameraSize(int, int);

    void clearScreen();
    void presentScreen();

    auto* getRender() { return renderer; }

private:
    std::string& name;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Rect camera;

    bool initSDL(Uint32 SDL = SDL_INIT_EVERYTHING);
    void renderPlayer(GameState& state, int x, int y);
};

#endif
