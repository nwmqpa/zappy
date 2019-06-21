/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#include <iostream>
#include "Window.hpp"

Window::Window(std::string &name, int x, int y)
    :name(name),
    x(0),
    y(0)
{
#ifdef __SWITCH__
    if (inits(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK, IMG_INIT_PNG)) {
#else
    if (inits()) {
#endif
#ifdef __SWITCH__
        SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);
#else
        window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_RESIZABLE);
#endif
        if (window == NULL)
            throw GraphicalException("Window error", "SDL_CreateWindow");
#ifndef __SWITCH__
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#endif
        if (renderer == NULL)
            throw GraphicalException("Renderer error", "SDL_CreateRenderer");
        SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

bool Window::inits(Uint32 sdl, Uint32 img)
{
    if (SDL_Init(sdl) < 0) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    } else if (IMG_Init(img) < 0) {
        std::cout << "IMG Error: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}
/*void Window::client_event()
{
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                destroy();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_DOWN:
                        addY(10);
                        break;
                    case SDLK_UP:
                        addY(-10);
                        break;
                    case SDLK_LEFT:
                        addX(-10);
                        break;
                    case SDLK_RIGHT:
                        addX(10);
                        break;
                    case SDLK_KP_PLUS:
                        scale(10);
                        break;
                    case SDLK_KP_MINUS:
                        scale(-10);
                        break;
                }

        }
    }
}

void Window::scale(int value)
{
    int old;

    for (unsigned int i = 0; i < tileList.size(); i++) {
        old = tileList[i]->getScale();
        tileList[i]->setScale(old += value);
    }
}
*/
void Window::addY(int value, std::vector<Tile *> tileList)
{
    int old;

    y += value;
    for (unsigned int i = 0; i < tileList.size(); i++) {
        old = tileList[i]->getY();
        tileList[i]->setY(old += value);
    }
}

void Window::addX(int value, std::vector<Tile *> tileList)
{
    int old = 0;

    x += value;
    for (unsigned int i = 0; i < tileList.size(); i++) {
        old = tileList[i]->getX();
        tileList[i]->setX(old += value);
    }
}

void Window::drawTile(std::vector<Tile *> tileList, srv_map_size_t &mapSize)
{
    int w, h;
    SDL_Rect pos;
    std::vector<Tile *>::iterator it = tileList.begin();

    SDL_GetWindowSize(window, &w, &h);
    for (; it != tileList.end(); it++) {
        if ((*it)->getTileInfo() == NULL)
            throw GraphicalException("Tile error", "srv_tile_content");
        pos.x = (w / 2 - (mapSize.x / 2) + x) +
            ((*it)->getPosX() - (*it)->getPosY()) *
            ((*it)->getSurface()->w / 2) - ((*it)->getSurface()->w / 2);
        pos.y = (h / 2 - ((mapSize.y) / 2) + y) +
            ((*it)->getTileInfo()->x + (*it)->getTileInfo()->y) *
            ((*it)->getSurface()->h / 2) - (((*it)->getTileInfo()->x +
            (*it)->getTileInfo()->y) * 64) - (mapSize.y / 2 *
            (*it)->getSurface()->h) ;
        pos.w = (*it)->getSurface()->w;
        pos.h = (*it)->getSurface()->h;
        if (SDL_RenderCopy(renderer, (*it)->getTmp(), NULL, &pos) < 0)
            throw GraphicalException("Render copy error", "SDL_RenderCopy");
    }
}

void Window::clearScreen()
{
    SDL_RenderClear(renderer);
}

void Window::PresentScreen()
{
    SDL_RenderPresent(renderer);
}

void Window::destroyer()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
