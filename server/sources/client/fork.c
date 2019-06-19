/*
** EPITECH PROJECT, 2019
** fork.c
** File description:
** Fork command file.
*/

#include "client_commands.h"
#include "logger.h"

// TODO: Adding fork.
char *fork_client(client_t *client, server_t *server)
{
    team_t *team = get_client_team(client, server);
    client_t *new = client_create(-2);

    if (add_client_to_team(server, new, team->name) == 0) {
        errorl("Cannot fork no more space in team %s.\n", team->name);
        return strdup("ko");
    }
    return strdup("ok");
}


