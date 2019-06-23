/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GameState
*/

#include "GameState.hpp"

GameState::GameState(std::string ip, short int port)
    : lastData(nullptr)
    , tileList()
    , protocol(ip, port)
    , resourcesManager([](std::string path, SDL_Renderer *render) {
        auto img = SDL_LoadBMP(path.c_str());
        if (img == nullptr)
            throw GraphicalException("BMP loading error on Tile", "SDL_LoadBMP Tile");
        auto tmp = SDL_CreateTextureFromSurface(render, img);
        if (tmp == nullptr)
            throw GraphicalException("Buffering texture creation error", "SDL_CreateTextureFromSurface");
        std::tuple<SDL_Texture *, SDL_Surface *> tuple(tmp, img);
        return tuple;
    })
{
    this->camera.center.x = 0;
    this->camera.center.y = 0;
    this->camera.scale.x = 4;
    this->camera.scale.y = 4;
}
