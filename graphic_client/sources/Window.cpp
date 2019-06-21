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
        /*pos.x = (w / 2 - (mapSize->x / 2)) +
            ((*it)->getPosX() - (*it)->getPosY()) *
            ((*it)->getSurface()->w / 2) - ((*it)->getSurface()->w / 2) + camera.x;
        pos.y = (h / 2 - (mapSize->y / 2)) +
            ((*it)->getTileInfo()->x + (*it)->getTileInfo()->y) *
            ((*it)->getSurface()->h / 2) - (((*it)->getTileInfo()->x +
            (*it)->getTileInfo()->y) * 64) - (mapSize->y / 2 *
            (*it)->getSurface()->h) + camera.y;
        pos.w = (*it)->getSurface()->w;
        pos.h = (*it)->getSurface()->h;*/
        pos.x = Isometry::setPositionX(w, x, (*it)->getPosX(),
                (*it)->getPosY(), (*it)->getSurface()->w, camera.x);
        pos.y = Isometry::setPositionY(h, y, (*it)->getPosX(),
                (*it)->getPosY(), (*it)->getSurface()->h, camera.y);
        pos.h = Isometry::setHeight((*it)->getSurface()->h);
        pos.w = Isometry::setWidth((*it)->getSurface()->w);
        (*it)->setArea(pos);
        if (SDL_RenderCopy(renderer, (*it)->getTmp(), nullptr, &pos) < 0)
            throw GraphicalException("Render copy error", "SDL_RenderCopy");
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
