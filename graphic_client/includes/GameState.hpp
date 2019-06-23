/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GameState
*/

#include <tuple>
#include "Player.hpp"
#include "Protocol.hpp"
#include "Tile.hpp"
#include "Egg.hpp"
#include "Team.hpp"
#include "ResourcesManager.hpp"

#pragma once

struct Camera {
    struct {
        float x;
        float y;
    } center;
    struct {
        float x;
        float y;
    } scale;
};

struct GameState {
    GameState(std::string ip, short int port);

    pkt_header_t lastHeader;
    void* lastData;
    Camera camera;
    std::vector<Tile *> tileList;
    std::vector<Player *> playerList;
    std::vector<Egg *> eggs;
    std::vector<Team *> teams;
    srv_map_size_t mapSize;
    bool isActive;
    Protocol protocol;
    ResourcesManager<std::tuple<SDL_Texture *, SDL_Surface *>, SDL_Renderer *> resourcesManager;
};
