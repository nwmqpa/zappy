/*
** EPITECH PROJECT, 2019
** command.c
** File description:
** commands queue handling.
*/

#include "logger.h"
#include "client_commands.h"

static const command_t COMMANDS[] = {
    {"Fork", fork_client, 4},
    {"Eject", eject, 5},
    {"Forward", forward, 7},
    {"Left", left, 4},
    {"Right", forward, 5},
    {"Look", look, 4},
    {"Incante", incante, 7},
    {"Connect_nbr", connect_nbr, 11},
    {NULL, NULL, 0}
};

static const command_param_t COMMANDS_PARAM[] = {
    {"Broadcast", broadcast, 9},
    {"Take", take, 4},
    {"Set", set, 3},
    {NULL, NULL, 0}
};

int add_command(client_t *client, char *command)
{
    size_t len = len_list(client->commands);

    if (len < 10) {
        debugl("Registering command[%d] - %s.\n", len, command);
        insert_head_list(client->commands, (void *) command);
        return 0;
    } else {
        infol(
        "Cannot register command, there is already 10 commands registered.\n");
        return -1;
    }
}

static char *iter_command(client_t *client, server_t *server, const char *command)
{
    for (int i = 0; COMMANDS_PARAM[i].name; ++i) {
        if (strncmp(COMMANDS_PARAM[i].name ,command,
                    COMMANDS_PARAM[i].len) == 0) {
            return COMMANDS_PARAM[i].function(client, server,
                    command + COMMANDS_PARAM[i].len);
        }
    }
    for (int i = 0; COMMANDS[i].name; ++i) {
        if (strncmp(COMMANDS[i].name ,command, COMMANDS[i].len) == 0) {
            return COMMANDS[i].function(client, server);
        }
    }
    if (strncmp("status", command, 6) == 0) {
        debugl("Status %s\n", command);
        return server_status(server, command + 6);
    }
    errorl("Command not found %s.\n", command);
    return strdup("ko\n");
}

int process_command(client_t *client, server_t *server)
{
    char *command;

    if (is_empty_list(client->commands))
        return -1;
    command = (char *) pop_list(client->commands, 0);
    client->to_send = iter_command(client, server, command);
    debugl("Handling command %s.\n", command);
    return 0;
}

size_t len_command(client_t *client)
{
    return len_list(client->commands);
}
