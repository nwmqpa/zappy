/*
** EPITECH PROJECT, 2019
** protocols_graphic.h
** File description:
** Protocol functions.
*/

#pragma once

#include "protocols.h"
#include "server.h"
#include "logger.h"

/// Register all handlers onto the server.
void register_all_handlers(server_t *server);

/// Handle a graphic packet.
int handle_packet(int socket, server_t *server);

int map_size(const void *data);
int map_content(const void *data);
int tile_content(const void *data);

int teams_name(const void *data);

int player_pos(const void *data);
int player_level(const void *data);
