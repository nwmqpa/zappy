/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#include "SDL.hpp"

WindowCreator::WindowCreator(const char *name, int x, int y, Uint32 flags)
{
    if (Inits()) {
        window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, x, y, flags);
        if (window != NULL)
            screen = SDL_GetWindowSurface(window);
    }
    /*Initialisation de la fenêtre et des modules de SDL*/
}

WindowCreator::~WindowCreator()
{}

bool WindowCreator::Inits(Uint32 SDL, Uint32 IMG)
{
    if (SDL_Init(SDL) < 0) {
        printf("SDL Error: %s.\n", SDL_GetError());
        return false;
    } else if (IMG_Init(IMG) < 0) {
        printf("IMG Error: %s.\n", IMG_GetError());
        return false;
    }
    return true;
}

void WindowCreator::Life()
{
    while (heart) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    Destroy();
            }
        }
        if (!Update())
            Destroy();
    }
}

bool WindowCreator::Update()
{
    if (SDL_UpdateWindowSurface(window) < 0) {
        printf("Update Error: %s.\n", SDL_GetError());
        return false;
    }
    return true;
}

void WindowCreator::Destroy()
{
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    heart = false;
}
