/*
** EPITECH PROJECT, 2019
** eject.c
** File description:
** Ejection command file.
*/

#include "client.h"

// TODO: Implement.
char *eject(client_t *client, server_t *server)
{
    client->cooldown = 7;
    return "ok";
}
