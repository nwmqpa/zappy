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
    int *sock = (int *) data;
    server_t *server = (server_t *) (data + sizeof(int));
    clt_player_pos_t payload;
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

    read(*sock, &payload, CLT_PLAYER_POS_LEN);
    fill_payload(&payload, &response.payload, server);
    write(*sock, &response, PKT_HDR_LEN + SRV_PLAYER_POS_LEN);
    return 0;
}
