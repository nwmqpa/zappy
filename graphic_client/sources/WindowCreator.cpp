/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#include <iostream>
#include "WindowCreator.hpp"

WindowCreator::WindowCreator(std::string &name, int x, int y)
    :name(name)
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

bool WindowCreator::inits(Uint32 sdl, Uint32 img)
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

void WindowCreator::client_event()
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

void WindowCreator::scale(int value)
{
    int old;

    for (unsigned int i = 0; i < tileList.size(); i++) {
        old = tileList[i]->getScale();
        tileList[i]->setScale(old += value);
    }
}

void WindowCreator::addY(int value)
{
    int old;

    for (unsigned int i = 0; i < tileList.size(); i++) {
        old = tileList[i]->getY();
        tileList[i]->setY(old += value);
    }
}

void WindowCreator::addX(int value)
{
    int old = 0;

    for (unsigned int i = 0; i < tileList.size(); i++) {
        old = tileList[i]->getX();
        tileList[i]->setX(old += value);
    }
}

void WindowCreator::drawTile()
{
    for (unsigned int i = 0; i < tileList.size(); i++)
        tileList[i]->draw(renderer, window);
}

void WindowCreator::display()
{
    SDL_RenderClear(renderer);
    update();
    SDL_RenderPresent(renderer);
}

void WindowCreator::update()
{
    drawTile();
    client_event();
}

/*void WindowCreator::addAllTile(srv_map_size_t newMap)
{
    for (int i = 0; i < (newMap.x * newMap.y); i++) {
        tileList.push_back(new Tile(REALPATH("back.bmp"), renderer));
        tileList[i].setMapSize(*newMap);
    }
}*/

/*void WindowCreator::updateTile(srv_tile_content_t newTileContent)
{
    std::vector<Tile *>::iterator it;

    for (; it < tileList.end(); it++) {
        if (it.getMap() != NULL) {
            if (newTileContent != it && it.getX() == newTileContent.x
                    && it.getY() == newTileContent.y)
                it.setTileContent(*newTileContent);
        }
    }
}*/

void WindowCreator::destroy()
{
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
