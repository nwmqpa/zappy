/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#include "Window.hpp"
#include <iostream>

Window::Window(std::string& name, int x, int y)
    : name(name)
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
        camera = { 0, 0, 0, 0 };
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

void Window::setCameraSize(int w, int h)
{
    camera.w = w;
    camera.h = h;
}

void Window::move(float x, float y)
{
    camera.x += x;
    camera.y += y;
}

void Window::render(GameState& state, int x, int y)
{
    int w, h;
    SDL_Rect pos;
    SDL_GetWindowSize(window, &w, &h);
    setCameraSize(h, w);

    for (auto tile: state.tileList) {
        if (tile->getTileInfo() == nullptr)
            continue;
        pos.x = ((tile->getPosX() * tile->getSurface()->w) - (tile->getPosY() * tile->getSurface()->w)) / 2;
        pos.y = ((tile->getPosX() * tile->getSurface()->h) + (tile->getPosY() * tile->getSurface()->h)) / 3.25;
        pos.x /= state.camera.scale.x;
        pos.y /= state.camera.scale.y;
        pos.x += (w / 2) - tile->getSurface()->w / 2 / state.camera.scale.x;
        pos.y += (h / 2) - (tile->getSurface()->h / 2) * (y / 2 / state.camera.scale.y);
        pos.x += state.camera.center.x;
        pos.y += state.camera.center.y;
        pos.h = Isometry::setHeight(tile->getSurface()->h, state.camera);
        pos.w = Isometry::setWidth(tile->getSurface()->w, state.camera);
        tile->setArea(pos);
        if (SDL_RenderCopy(renderer, tile->getTmp(), nullptr, &pos) < 0)
            throw GraphicalException("Render copy error", "SDL_RenderCopy");
    }
}

void Window::renderPlayer(GameState& state)
{
    std::vector<Player*> playerList = state.playerList;
    std::vector<Tile*> tileList = state.tileList;

    SDL_Rect pos;

    for (auto player: playerList) {
        for (auto tile: tileList) {
            if (tile->getPosX() == player->getX() && tile->getPosY() == player->getY()) {
                pos.x = ((player->getSurface()->w) - (player->getSurface()->w) / 2);
                pos.y = ((player->getSurface()->h) + (player->getSurface()->h) / 2);
                pos.x /= state.camera.scale.x;
                pos.y /= state.camera.scale.y;
                pos.x += (tile->getArea().w / 2) - (player->getSurface()->w / 2) / state.camera.scale.x;
                pos.y += (tile->getArea().h / 2) - (player->getSurface()->h / 2) * (1 / 2 / state.camera.scale.y);
                pos.w = Isometry::setHeight(player->getSurface()->w, state.camera);
                pos.h = Isometry::setHeight(player->getSurface()->h, state.camera);
                if (SDL_RenderCopy(renderer, player->getTmp(), nullptr, &pos) < 0)
                    throw GraphicalException("Render copy error", "SDL_RenderCopy");
            }
        }
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
