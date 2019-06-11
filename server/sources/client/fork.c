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
    team_t *team = get_client_team(client, server);
    client_t *new = client_create(-2);

    add_client_to_team(server, new, team->name);
    client->cooldown = 42;
    return "ok";
}


