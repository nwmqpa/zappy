/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#include <iostream>
#include "Window.hpp"

Window::Window(std::string &name, int x, int y)
    :name(name)
{
#ifdef __SWITCH__
    if (initSDL(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK, IMG_INIT_PNG)) {
#else
    if (initSDL()) {
#endif
#ifdef __SWITCH__
        SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);
#else
        window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_RESIZABLE);
#endif
        if (window == nullptr)
            throw GraphicalException("Window error", "SDL_CreateWindow");
#ifndef __SWITCH__
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#endif
        if (renderer == nullptr)
            throw GraphicalException("Renderer error", "SDL_CreateRenderer");
        SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255);
        camera = {0, 0, 0, 0};
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

bool Window::initSDL(Uint32 sdl)
{
    if (SDL_Init(sdl) < 0) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Window::move(float x, float y)
{
    camera.x += x;
    camera.y += y;
}

void Window::setCameraSize(int h, int w)
{
    camera.h = h;
    camera.w = w;
}

void Window::drawTile(std::vector<Tile *> tileList, int x, int y)
{
    int w, h;
    SDL_Rect pos;
    auto it = tileList.begin();

    SDL_GetWindowSize(window, &w, &h);
    setCameraSize(h, w);

    for (; it != tileList.end(); it++) {
        if ((*it)->getTileInfo() == nullptr)
            continue;
        std::cout << (*it)->getPosX() << ", " << (*it)->getPosY() << std::endl;
        pos.x = ((*it)->getPosX() * (*it)->getSurface()->w) - ((*it)->getPosY() * (*it)->getSurface()->h);
        pos.y = (((*it)->getPosX() * (*it)->getSurface()->w) + ((*it)->getPosY() * (*it)->getSurface()->h)) / 2;
        //pos.x = Isometry::setPositionX(w, x, (*it)->getPosX(), (*it)->getPosY(), (*it)->getSurface()->w, camera.x);
        //pos.y = Isometry::setPositionY(h, y, (*it)->getPosX(), (*it)->getPosY(), (*it)->getSurface()->h, camera.y);
        pos.h = Isometry::setHeight((*it)->getSurface()->h);
        pos.w = Isometry::setWidth((*it)->getSurface()->w);
        std::cout << pos.x << ", " << pos.y << ", " << pos.h << ", " << pos.w << std::endl;
        if (SDL_RenderCopy(renderer, (*it)->getTmp(), nullptr, &pos) < 0)
            throw GraphicalException("Render copy error", "SDL_RenderCopy");
        //std::cout << camera.x << " " << camera.y << std::endl;
    }
}

void Window::clearScreen()
{
    SDL_RenderClear(renderer);
}

void Window::presentScreen()
{
    SDL_RenderPresent(renderer);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
