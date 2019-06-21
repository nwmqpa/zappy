/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GameState
*/

#include "Protocol.hpp"
#include "Tile.hpp"

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
    void *lastData;
    Camera camera;
    std::vector<Tile *> tileList;
    srv_map_size_t mapSize;
    bool isActive;
    Protocol protocol;
};
