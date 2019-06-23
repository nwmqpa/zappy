/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#pragma once

#include <string>
#include <tuple>
#include "protocols.h"
#include "Window.hpp"
#include "GameState.hpp"

typedef void (*data_processor_t)(GameState &, Window &);

class Handlers {
    public:
        static void gotMapSize(GameState &state, Window &window);
        static void gotDeathPlayer(GameState &state, Window &window);
        static void gotTileContent(GameState &state, Window &window);
        static void gotNewPlayerConnect(GameState &state, Window &window);
        static void gotPlayerPosition(GameState &state, Window &window);
        static void gotPlayerLevel(GameState &state, Window &window);
        static void gotEggLayed(GameState &state, Window &window);
        static void gotEggHatching(GameState &state, Window &window);
        static void gotTeamsNames(GameState &state, Window &window);

        const static std::vector<std::tuple<GRAPHIC_PACKETS_FROM_SERVER, data_processor_t>> HANDLERS;
        const static std::vector<std::tuple<GRAPHIC_PACKETS_FROM_SERVER, std::string>> NAMES;
};

