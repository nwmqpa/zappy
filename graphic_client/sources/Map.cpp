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
        throw SDL_GetError();
    if (IMG_Init(IMG_INIT_PNG) < 0)
        throw IMG_GetError();
    else {
        _window = SDL_CreateWindow("Zappy", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        if (_window == NULL)
            throw SDL_GetError();
        else
            _screen = SDL_GetWindowSurface(_window);
    }
    /*Initialisation de la fenêtre et des modules de SDL*/
}

void Map::Quit()
{
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
    _isAlive = false;
}

void Map::Update()
{
    SDL_UpdateWindowSurface(_window);
    /*Update*/
}

void Map::mainCycle()
{
    while (_isAlive) {
        while (SDL_PollEvent(&_event) != 0) {
            switch (_event.type) {
                case SDL_QUIT:
                    this->Quit();
            }
        }
        Update();
    }
    /*Boucle de vie de la fenêtre/gestion des events et update de la fenêtre*/
}

void Map::getSize()
{
    try {
        /*Récupération de la taille de la carte (srv_map_size_t)*/
    } catch (std::exception *error) {
        _isAlive = false;
        throw (error->what());
    }
    /*Récupération de la taille de la carte*/
}

void Map::generateMap()
{
    try {
        printf("generation\n");
        for (unsigned int i = 0; i < (_map_size->x * _map_size->y); i += 1) {
            /*Récupération de la composition des chaque case (srv_tile_content_t)*/
            //srv_tile_content_t *tmp = &case;
            if (_map.size() > 0 && _map[i]->getTile() != tmp)
                _map[i]->setTile(tmp);
            else
                _map.push_back(new Case(tmp, _screen));
        }
    } catch (std::exception *error) {
        _isAlive = false;
    }
    /*Génération et update des informations des cases de la carte*/
}
