/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GameState
*/

#include "protocols.h"

struct GameState {
    pkt_header_t lastHeader;
    void *lastData;
};
