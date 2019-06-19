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
    clt_time_unit_request_t payload;
    const struct {
        int sock;
        server_t *server;
    } *datas = data;
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

    read(datas->sock, &payload, CLT_TIME_UNIT_REQUEST_LEN);
    response.payload.freq = datas->server->freq;
    write(datas->sock, &response, PKT_HDR_LEN + SRV_TIME_UNIT_REQUEST_LEN);
    return 0;
}

int time_change(const void *data)
{
    clt_time_unit_change_t payload;
    const struct {
        int sock;
        server_t *server;
    } *datas = data;

    read(datas->sock, &payload, CLT_TIME_UNIT_REQUEST_LEN);
    datas->server->freq = payload.freq;
    return 0;
}
