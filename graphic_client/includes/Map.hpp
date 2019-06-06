/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical client
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

#include <vector>
#include "protocols.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "Case.hpp"

class Map {
    public:
        Map();
        ~Map();

        void initScreen();
        void getSize();
        void generateMap();
        void mainCycle();
        void Update();
        void Quit();

    private:
        SDL_Window *_window;
        SDL_Surface *_screen;
        SDL_Event _event;

        bool _isAlive;
        std::vector<Case *> _map;

        srv_map_size_t *_map_size;
};

#endif
