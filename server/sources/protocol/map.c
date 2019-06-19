/*
** EPITECH PROJECT, 2019
** map.c
** File description:
** Map graphic protocol functions.
*/

#include "protocols_graphic.h"
#include "server.h"

int map_size(const void *data)
{
    const struct {
        int sock;
        server_t *server;
    } *datas = data;

    struct {
        pkt_header_t header;
        srv_map_size_t payload;
    } response = {
        {
            .id = SRV_MAP_SIZE,
            .subid = 0,
            .version = PROTOCOL_VERSION,
            .size = SRV_MAP_SIZE_LEN
        },
        {
            .x = datas->server->width,
            .y = datas->server->height
        }
    };

    write(datas->sock, &response, SRV_MAP_SIZE_LEN + PKT_HDR_LEN);
    return 0;
}

int map_content(const void *data)
{
    return 0;
}

static void fill_payload(tile_t *tile, srv_tile_content_t *payload,
        unsigned int x, unsigned int y)
{
    payload->x = x;
    payload->y = y;
    payload->q0 = tile->inventory.inv.food;
    payload->q1 = tile->inventory.inv.linemate;
    payload->q2 = tile->inventory.inv.deraumere;
    payload->q3 = tile->inventory.inv.sibur;
    payload->q4 = tile->inventory.inv.mendiane;
    payload->q5 = tile->inventory.inv.phiras;
    payload->q6 = tile->inventory.inv.thystame;
    payload->players = tile->nb_player;
}

int tile_content(const void *data)
{
    const struct {
        int sock;
        server_t *server;
    } *datas = data;

    clt_tile_content_t payload;
    tile_t *tile = NULL;
    struct {
        pkt_header_t header;
        srv_tile_content_t payload;
    } response = {
        {   .id = SRV_MAP_SIZE,
            .subid = 0,
            .version = PROTOCOL_VERSION,
            .size = SRV_MAP_SIZE_LEN},
        {0}
    };

    read(datas->sock, &payload, CLT_TILE_CONTENT_LEN);
    tile = get_tile_map(datas->server->map, payload.x, payload.y);
    fill_payload(tile, &response.payload, payload.x, payload.y);
    write(datas->sock, &response, PKT_HDR_LEN + SRV_TILE_CONTENT_LEN);
    return 0;
}

