/*
** EPITECH PROJECT, 2019
** events.c
** File description:
** Events source file.
*/

#include "events.h"
#include "logger.h"

static const int NB_PACKET = 13;

static const struct {
    int id;
    int size;
} ID_SIZE[] = {
    {SRV_NEW_PLAYER_CONNECT, SRV_NEW_PLAYER_CONNECT_LEN},
    {SRV_EXPULSION, SRV_PLAYER_EXPULSION_LEN},
    {SRV_BROADCAST, SRV_BROADCAST_MSG_LEN},
    {SRV_INCANTATION_START, SRV_START_INCANTATION_LEN},
    {SRV_INCANTATION_END, SRV_END_INCANTATION_LEN},
    {SRV_EGG_LAYING, SRV_PLAYER_EGG_LAYING_LEN},
    {SRV_RESOURCE_DROP, SRV_PLAYER_RESOURCE_DROPPED_LEN},
    {SRV_PLAYER_DEATH, SRV_PLAYER_DEATH_LEN},
    {SRV_EGG_LAYED, SRV_PLAYER_EGG_LAYED_LEN},
    {SRV_EGG_HATCHING, SRV_PLAYER_EGG_HATCHING_LEN},
    {SRV_PLAYER_CONNECT_EGG, SRV_PLAYER_EGG_CONNECTION_LEN},
    {SRV_END_GAME, SRV_END_GAME_LEN}
};

int add_event(server_t *server, int id, void *payload)
{
    insert_head_list(server->events, payload);
    return 0;
}

static int get_packet_size(int id) {
    for (int i = 0; i < NB_PACKET; ++i) {
        if (ID_SIZE[i].id == id)
            return ID_SIZE[i].size;
    }
    return 0;
}

static int send_event(server_t *server, event_t *event)
{
    int packet_size = get_packet_size(event->id);
    struct {
        pkt_header_t header;
        void *payload;
    } send = {
        {
            .id = event->id,
            .version = PROTOCOL_VERSION,
            .subid = 0,
            .size = packet_size
        },
        .payload = event->payload
    };

    return write(*(int *) get_list(server->graphic_clients, 0), &send,
            packet_size + PKT_HDR_LEN);
}

void handle_events(server_t *server)
{
    event_t *event = pop_list(server->events, 0);

    while (event) {
        if (send_event(server, event) == -1)
            errorl("Error while writing to graphic client.\n");
        event = pop_list(server->events, 0);
    }
}
