/*
** EPITECH PROJECT, 2019
** fork.c
** File description:
** Fork command file.
*/

#include "client_commands.h"

// TODO: Adding fork.
char *fork_client(client_t *client, server_t *server)
{
    client->cooldown = 42;
    return "ok";
}
