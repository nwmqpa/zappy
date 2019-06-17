/*
** EPITECH PROJECT, 2019
** time.c
** File description:
** Time handler.
*/

#include "client.h"
#include "server.h"
#include "protocols.h"

int time_request(const void *data)
{
    int *sock = (int *) data;
    server_t *server = (server_t *) (data + sizeof(int));
    clt_time_unit_request_t payload;
    struct {
        pkt_header_t header;
        srv_time_unit_request_t payload;
    } response = {
        {   .id = SRV_TIME_UNIT_REQUEST,
            .subid = 0,
            .size = SRV_TIME_UNIT_REQUEST,
            .version = PROTOCOL_VERSION },
        {0}
    };

    read(*sock, &payload, CLT_TIME_UNIT_REQUEST_LEN);
    response.payload.freq = server->freq;
    write(*sock, &response, PKT_HDR_LEN + SRV_TIME_UNIT_REQUEST_LEN);
    return 0;
}

int time_change(const void *data)
{
    int *sock = (int *) data;
    server_t *server = (server_t *) (data + sizeof(int));
    clt_time_unit_change_t payload;

    read(*sock, &payload, CLT_TIME_UNIT_REQUEST_LEN);
    server->freq = payload.freq;
    return 0;
}
