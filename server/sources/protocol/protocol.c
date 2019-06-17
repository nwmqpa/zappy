/*
** EPITECH PROJECT, 2019
** protocol.c
** File description:
** Main file of the protocol graphic source code.
*/

#include "protocols_graphic.h"

static const phr_t REGISTER = {
    .size = 0,
    .handlers = {
        {CLT_MAP_SIZE, 0, "map_size", map_size},
        {CLT_TILE_CONTENT, 0, "tile_content", tile_content},
        {CLT_MAP_CONTENT, 0, "map_content", map_content},
        {CLT_TEAMS_NAMES, 0, "teams_name", teams_name},
        {CLT_PLAYER_POSITION, 0, "player_pos", player_pos},
        {0, 0, NULL, NULL}
    }
};

static void register_all_handlers(server_t *server)
{

}

static int handle(pkt_header_t *pkt, server_t *server, int sock)
{
    const struct data_s {
        int sock;
        server_t *server;
    } data = { .sock = sock, .server = server };
    pkt_handler_t **reg = REGISTER.handlers;

    for (int i = 0; reg[i]->handler; ++i) {
        if (reg[i]->id == pkt->id) {
            debugl("Running server request %s.\n", reg[i]->name);
            return reg[i]->handler((const void *) &data);
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
