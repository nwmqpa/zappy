/*
** EPITECH PROJECT, 2019
** protocol.c
** File description:
** Main file of the protocol graphic source code.
*/

#include "protocols_graphic.h"

static const int HANDLER_NBR = 10;

static const pkt_handler_t MAP_SIZE_H = {CLT_MAP_SIZE, 0, "map_size", map_size};

static const pkt_handler_t TILE_CONTENT_H =
    {CLT_TILE_CONTENT, 0, "tile_content", tile_content};

static const pkt_handler_t MAP_CONTENT_H =
    {CLT_MAP_CONTENT, 0, "map_content", map_content};

static const pkt_handler_t TEAMS_NAME_H =
    {CLT_TEAMS_NAMES, 0, "teams_name", teams_name};

static const pkt_handler_t PLAYER_POS_H =
    {CLT_PLAYER_POSITION, 0, "player_pos", player_pos};

static const pkt_handler_t LAST_H = {0, 0, NULL, NULL};

void register_all_handlers(server_t *server)
{
    server->reg.handlers = malloc(sizeof(pkt_handler_t *) * HANDLER_NBR);
    server->reg.handlers[0] = &MAP_SIZE_H;
    server->reg.handlers[1] = &TILE_CONTENT_H;
    server->reg.handlers[2] = &MAP_CONTENT_H;
    server->reg.handlers[3] = &TEAMS_NAME_H;
    server->reg.handlers[4] = &PLAYER_POS_H;
    server->reg.handlers[5] = &LAST_H;
}

static int handle(pkt_header_t *pkt, server_t *server, int sock)
{
    const struct data_s {
        int sock;
        server_t *server;
    } data = { .sock = sock, .server = server };
    pkt_handler_t **handlers = server->reg.handlers;

    for (int i = 0; handlers[i]; ++i) {
        if (handlers[i]->id == pkt->id) {
            debugl("Running server request %s.\n", handlers[i]->name);
            return handlers[i]->handler((const void *) &data);
        }
    }
    debugl("Request not find it's a custom");
    return -1;
}

int handle_packet(int socket, server_t *server)
{
    pkt_header_t packet;
    read(socket, &packet, PKT_HDR_LEN);
    return handle(&packet, server, socket);
}
