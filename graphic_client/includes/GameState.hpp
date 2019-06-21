/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GameState
*/

#include "Protocol.hpp"
#include "Tile.hpp"

struct GameState {
    GameState(std::string ip, short int port);
    pkt_header_t lastHeader;
    void *lastData;

    std::vector<Tile *> tileList;
    srv_map_size_t mapSize;
    bool isActive;
    Protocol protocol;
};
