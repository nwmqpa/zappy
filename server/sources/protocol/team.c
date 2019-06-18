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
    server_t *server = (server_t *) data + sizeof(int);
    int *sock = (int *) data;
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

    for (int i = 0; server->teams[i]; ++i) {
        memcpy(&response.payload.team_name, server->teams[i]->name,
                strlen(server->teams[i]->name));
        write(*sock, &response, PKT_HDR_LEN + SRV_TEAMS_NAMES_LEN);
    }
    return 0;
}
