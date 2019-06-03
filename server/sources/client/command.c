/*
** EPITECH PROJECT, 2019
** command.c
** File description:
** commands queue handling.
*/

#include "logger.h"
#include "client_commands.h"

static const command_t COMMANDS[] = {
    {"fork", fork_client},
    {"eject", eject},
    {NULL, NULL}
};

void add_command(client_t *client, char *command)
{
    size_t len = len_list(client->commands);

    if (len < 10) {
        debugl("Registering command[%d] - %s.\n", len, command);
        insert_head_list(client->commands, (void *) command);
    } else {
        infol(
        "Cannot register command, there is already 10 commands registered.\n");
    }
}

int process_command(client_t *client)
{
    char *command;

    if (is_empty_list(client->commands))
        return -1;
    command = (char *) pop_list(client->commands, 0);
    debugl("Handling command %s.\n", command);
    return 0;
}

size_t len_command(client_t *client)
{
    return len_list(client->commands);
}

char *handle_client_command(client_t *client, server_t *server,
        const char *command)
{
    char *ret = NULL;

    if (strcmp(command, "broadcast") == 0)
        return broadcast(client, server, command);
    for (int i = 0; COMMANDS[i].name; ++i) {
        if (strcmp(COMMANDS[i].name ,command) == 0) {
            ret = COMMANDS[i].function(client, server);
            break;
        }
    }
    if (ret == NULL)
        errorl("Command %s not found.\n", command);
    else
        dprintf(client->id, ret);
    return ret;
}
