/*
** EPITECH PROJECT, 2019
** protocol.c
** File description:
** Main file of the protocol graphic source code.
*/

#include "protocols_graphic.h"

static const pkt_handler_t PACKET_HANDLERS[CLT_CUSTOM] = {
    {CLT_PROTOCOL_ADDONS, 0, "protocol_addons", 0x0},
    {CLT_MAP_SIZE, 0, "map_size", map_size},
    {CLT_TILE_CONTENT, 0, "tile_content", tile_content},
    {CLT_MAP_CONTENT, 0, "map_content", map_content},
    {CLT_TEAMS_NAMES, 0, "teams_name", teams_name},
    {CLT_PLAYER_POSITION, 0, "player_pos", player_pos},
    {CLT_PLAYER_LEVEL, 0, "player_level", 0x0},
    {CLT_PLAYER_INVENTORY, 0, "player_inventory", 0x0},
    {CLT_TIME_UNIT_REQUEST, 0, "time_unit_request", time_request},
    {CLT_TIME_UNIT_CHANGE, 0, "time_unit_change", time_change},
    {CLT_CUSTOM, 0, "clt_custom", invalid_custom}
};

void register_pkt_handler(phr_t *registrar, pkt_handler_t *handler)
{
    size_t num_handlers = 0;

    if (registrar->handlers)
        for (; registrar->handlers[num_handlers]; num_handlers++);
    registrar->handlers = realloc(registrar->handlers,
    sizeof(pkt_handler_t *) * (num_handlers + 2));
    memset(registrar->handlers + num_handlers, 0, sizeof(pkt_handler_t *) * 2);
    if (!registrar->handlers) {
        fatall("Cannot allocate memory for packet handlers.");
        exit(84);
    }
    debugl("Registering `%s` packet handler.\n", handler->name);
    registrar->handlers[num_handlers] = handler;
}

void register_all_handlers(server_t *server)
{
    pkt_handler_t *temp = 0x0;

    for (size_t i = 0; i < CLT_CUSTOM; i++) {
        temp = malloc(sizeof(pkt_handler_t));
        memcpy(temp, &(PACKET_HANDLERS[i]), sizeof(pkt_handler_t));
        register_pkt_handler(&(server->reg), temp);
    }
}

static int handle(pkt_header_t *pkt, server_t *server, int sock)
{
    const struct {
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
    debugl("Handler not found.\n");
    return -1;
}

int handle_packet(int socket, server_t *server)
{
    pkt_header_t packet;
    if (read(socket, &packet, PKT_HDR_LEN) == 0)
        return -1;
    debugl("Graphic client sent a message.\n");
    handle(&packet, server, socket);
    return 0;
}
