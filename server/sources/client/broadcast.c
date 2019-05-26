/*
** EPITECH PROJECT, 2019
** broadcast.c
** File description:
** Broadcast command file.
*/

#include "client.h"

void send_to_clients(server_t *server, const char *text, size_t local_id)
{
    // TODO: Send to all client.
}

char *broadcast(client_t *client, server_t *server, const char *text)
{
    client->cooldown = 7;
    send_to_clients(server, text, client->id);
    return "ok";
}
