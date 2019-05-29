/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Map.hpp"

Map::Map()
{
    this->initScreen();
    this->getSize();
    this->generateMap();
}

Map::~Map()
{}

void Map::initScreen()
{
    _isAlive = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw new SDL_GetError();
    if (IMG_Init(IMG_INIT_PNG) < 0)
        throw new IMG_GetError();
    else {
        _window = SDL_CreateWindow("Zappy", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        if (_window == NULL)
            throw new SDL_GetError();
        else
            screen = SDL_GetWindowSurface(window);
    }
}

void Map::Quit()
{
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    this->setLife(false);
}

void Map::mainCycle()
{
    while (this->getLife()) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    this->Quit();
            }
        }
    }
}

void Map::getSize()
{
    try {
        _map_size = "appel API"
    } catch (std::exception *error) {
        this->setLife(false);
        throw (error.what());
    }
}

void Map::generateMap()
{
    try {
        for (int i = 0; i < (_map_size.x * _map_size.y); i += 1) {
            srv_tile_content_t *tmp = "appel API";
            if (_map.size() > 0 && _map[i].getTile() != tmp)
                _map[i].setTile(tmp);
            else
                _map.push_back(new Case(tmp));
        }
    } catch (std::exception *error) {
        this->setLife(false);
    }
}

