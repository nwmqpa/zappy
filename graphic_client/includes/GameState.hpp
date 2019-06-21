/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GameState
*/

#include "Protocol.hpp"
#include "Tile.hpp"
#include "Player.hpp"

struct GameState {
    GameState(std::string ip, short int port);
    pkt_header_t lastHeader;
    void *lastData;

    std::vector<Tile *> tileList;
    std::vector<Player *> playerList;
    srv_map_size_t mapSize;
    bool isActive;
    Protocol protocol;
};
