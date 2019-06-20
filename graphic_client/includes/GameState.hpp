/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GameState
*/

#include "protocols.h"
#include "Tile.hpp"

struct GameState {
    pkt_header_t lastHeader;
    void *lastData;

    std::vector<Tile *> tileList;
    srv_map_size_t *mapSize;
    bool mapRequest = false;
    bool isActive;
};
