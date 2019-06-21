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
    if (initSDL(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
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

void Window::render(GameState &state, int x, int y)
{
    int w, h;
    SDL_Rect pos;
    SDL_GetWindowSize(window, &w, &h);
    setCameraSize(h, w);

    for (auto it = state.tileList.begin(); it != state.tileList.end(); it++) {
        if ((*it)->getTileInfo() == nullptr)
            continue;
        pos.x = (((*it)->getPosX() * (*it)->getSurface()->w) - ((*it)->getPosY() * (*it)->getSurface()->w)) / 2;
        pos.y = (((*it)->getPosX() * (*it)->getSurface()->h) + ((*it)->getPosY() * (*it)->getSurface()->h)) / 3.25;
        pos.x /= state.camera.scale.x;
        pos.y /= state.camera.scale.y;
        pos.x += (w / 2) - (*it)->getSurface()->w / 2 / state.camera.scale.x;
        pos.y += (h / 2) - ((*it)->getSurface()->h / 2) * (y / 2 / state.camera.scale.y);
        pos.x += state.camera.center.x;
        pos.y += state.camera.center.y;
        pos.h = Isometry::setHeight((*it)->getSurface()->h, state.camera);
        pos.w = Isometry::setWidth((*it)->getSurface()->w, state.camera);
        (*it)->setArea(pos);
        if (SDL_RenderCopy(renderer, (*it)->getTmp(), nullptr, &pos) < 0)
            throw GraphicalException("Render copy error", "SDL_RenderCopy");
    }
}

/*
void Window::drawPlayer(GameState &state)
{
    std::vector<Player *> playerList = state.playerList;
    std::vector<Tile *> tileList = state.tileList;
    auto itPlayer = playerList.begin();
    auto itTile = tileList.begin();

    for (; itPlayer != playerList.end(); itPlayer++) {
        for (; itTile != tileList.end(); itTile++) {
            if ((*itTile)->getPosX() == (*itPlayer)->getX() &&
                (*itTile)->getPosY() == (*itPlayer)->getY()) {
                    pos.x = (((*itPlayer)->getSurface()->w) -
                            ((*itPlayer)->getSurface()->w) / 2);
                    pos.y = (((*itPlayer)->getSurface()->h) +
                            ((*itPlayer)->getSurface()->h) / 2);
                    pos.
            }
        }
    }
}
*/

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
