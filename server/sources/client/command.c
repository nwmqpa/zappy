/*
** EPITECH PROJECT, 2019
** command.c
** File description:
** commands queue handling.
*/

#include "logger.h"
#include "client_commands.h"

static const command_t COMMANDS[] = {
    {"Fork", fork_client, 4, 42},
    {"Eject", eject, 5, 7},
    {"Forward", forward, 7, 7},
    {"Left", left, 4, 7},
    {"Right", right, 5, 7},
    {"Look", look, 4, 7},
    {"Incante", incante, 7, 300},
    {"Connect_nbr", connect_nbr, 11, 0},
    {"Inventory", inventory, 9, 1},
    {NULL, NULL, 0, 0}
};

static const command_param_t COMMANDS_PARAM[] = {
    {"Broadcast", broadcast, 9, 7},
    {"Take", take, 4, 7},
    {"Set", set, 3, 7},
    {NULL, NULL, 0, 0}
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

static char *iter_command(client_t *client, server_t *server,
        const char *command)
{
    for (int i = 0; COMMANDS_PARAM[i].name; ++i) {
        if (strncmp(COMMANDS_PARAM[i].name, command,
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
    return strdup("ko");
}

int get_cooldown(const char *cmd)
{
    for (int i = 0; COMMANDS_PARAM[i].name; ++i)
        if (strncmp(COMMANDS_PARAM[i].name, cmd, COMMANDS_PARAM[i].len) == 0)
            return COMMANDS_PARAM[i].cooldown;
    for (int i = 0; COMMANDS_PARAM[i].name; ++i)
        if (strncmp(COMMANDS[i].name, cmd, COMMANDS[i].len) == 0)
            return COMMANDS[i].cooldown;
    return -1;
}

int prepare_command(client_t *client)
{
    if (is_empty_list(client->commands))
        return -1;
    client->to_exec = pop_list(client->commands, 0);
    debugl("Preparing command %s.\n", client->to_exec);
    client->cooldown = get_cooldown(client->to_exec);
    if (client->cooldown == -1) {
        errorl("Cannot find cooldown of %s.\n", client->commands);
        return -1;
    }
    return 0;
}

char *process_command(client_t *client, server_t *server)
{
    if (!client->to_exec || client->cooldown > 0) {
        errorl("No command to exec");
        return NULL;
    }
    return iter_command(client, server, client->to_exec);
}

size_t len_command(client_t *client)
{
    return len_list(client->commands);
}
