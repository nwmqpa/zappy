/*
** EPITECH PROJECT, 2019
** protocols_graphic.h
** File description:
** Protocol functions.
*/
#include "client.h"
#include "server.h"
#include "protocols.h"

int invalid_custom(const void *data)
{
    int *sock = (int *) data;
    clt_time_unit_request_t payload;
    struct {
        pkt_header_t header;
        srv_unknown_command_t payload;
    } response = {
        {   .id = SRV_UNKNOWN_COMMAND,
            .subid = 0,
            .size = SRV_UNKNOWN_COMMAND_LEN,
            .version = PROTOCOL_VERSION },
        {0}
    };

    read(*sock, &payload, 0);
    write(*sock, &response, PKT_HDR_LEN + SRV_UNKNOWN_COMMAND_LEN);
    return 0;
}
