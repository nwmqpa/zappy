/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#include <iostream>
#include "SDL.hpp"

WindowCreator::WindowCreator(const char *WINname, int x, int y)
{
#ifdef __SWITCH__
    if (inits(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK, IMG_INIT_PNG)) {
#else
    if (inits()) {
#endif
        heart = true;
        name = WINname;
#ifdef __SWITCH__
        SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);
#else
        window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_RESIZABLE);
#endif
        if (window == NULL)
            printf("Window Error%s\n", SDL_GetError());
#ifndef __SWITCH__
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#endif
        if (renderer == NULL)
            printf("Renderer Error%s\n", SDL_GetError());
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

WindowCreator::~WindowCreator()
{}

bool WindowCreator::inits(Uint32 SDL, Uint32 IMG)
{
    if (SDL_Init(SDL) < 0) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    } else if (IMG_Init(IMG) < 0) {
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
        old = tileList[i]->getPosY();
        tileList[i]->setPosY(old += value);
    }
}

void WindowCreator::addX(int value)
{
    int old = 0;

    for (unsigned int i = 0; i < tileList.size(); i++) {
        old = tileList[i]->getPosX();
        tileList[i]->setPosX(old += value);
    }
}

void WindowCreator::server_event()
{
//
}

void WindowCreator::drawTile()
{
    for (unsigned int i = 0; i < tileList.size(); i++)
        tileList[i]->draw(renderer, window);
}

void WindowCreator::life()
{
    while (heart) {
        SDL_RenderClear(renderer);
        update();
        SDL_RenderPresent(renderer);
    }
}

void WindowCreator::update()
{
    server_event();
    drawTile();
    client_event();
}

void WindowCreator::destroy()
{
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    heart = false;
}
