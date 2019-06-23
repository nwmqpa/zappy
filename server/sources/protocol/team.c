/*
** EPITECH PROJECT, 2019
** team.c
** File description:
** Team handler.
*/

#include "client.h"
#include "server.h"
#include "protocols.h"

int teams_name(const void *data)
{
    const struct { int sock; server_t *server; } *datas = data;
    struct {
        pkt_header_t header;
        srv_teams_names_t payload;
    } response = {
        {
            .id = SRV_TEAMS_NAMES,
            .subid = 0,
            .version = PROTOCOL_VERSION,
            .size = SRV_TEAMS_NAMES_LEN
        }, {{0}}
    };

    for (int i = 0; datas->server->teams[i]; ++i) {
        memcpy(&response.payload.team_name, datas->server->teams[i]->name,
                strlen(datas->server->teams[i]->name));
        write(datas->sock, &response, PKT_HDR_LEN + SRV_TEAMS_NAMES_LEN);
    }
    return 0;
}
