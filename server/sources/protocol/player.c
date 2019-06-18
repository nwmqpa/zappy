/*
** EPITECH PROJECT, 2019
** player.c
** File description:
** Player linked graphic protocol function.
*/

#include "client.h"
#include "server.h"
#include "protocols.h"

static void fill_payload(clt_player_pos_t *id, srv_player_pos_t *payload,
        server_t *server)
{
    client_t *client = get_cmp_list(server->clients, client_cmp,
            (void *) &id->player_num);

    payload->x = client->position.x;
    payload->y = client->position.y;
    payload->player_num = client->id;
    payload->orientation = client->direction;
}

int player_pos(const void *data)
{
    clt_player_pos_t payload;
    const struct {
        int sock;
        server_t *server;
    } *datas = data;
    struct {
        pkt_header_t header;
        srv_player_pos_t payload;
    } response = {
        {   .id = SRV_PLAYER_POSITION,
            .subid = 0,
            .size = SRV_PLAYER_POS_LEN,
            .version = PROTOCOL_VERSION },
        {0}
    };

    read(datas->sock, &payload, CLT_PLAYER_POS_LEN);
    fill_payload(&payload, &response.payload, datas->server);
    write(datas->sock, &response, PKT_HDR_LEN + SRV_PLAYER_POS_LEN);
    return 0;
}

int player_level(const void *data)
{
    client_t *client = NULL;
    clt_player_level_t payload;
    const struct {
        int sock;
        server_t *server;
    } *datas = data;
    struct {
        pkt_header_t header;
        srv_player_level_t paylaod;
    } response = {{
            .id = SRV_PLAYER_LEVEL,
            .subid = 0,
            .version = PROTOCOL_VERSION,
            .size = SRV_PLAYER_LEVEL_LEN}, {0}
    };

    read(datas->sock, &payload, CLT_PLAYER_LEVEL_LEN);
    response.paylaod.player_num = payload.player_num;
    client = get_cmp_list(datas->server->clients, client_cmp,
            (void *) &payload.player_num);
    response.paylaod.level = client->level;
    return write(datas->sock, &response, PKT_HDR_LEN + SRV_PLAYER_LEVEL_LEN);
}
