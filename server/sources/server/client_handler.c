/*
** EPITECH PROJECT, 2019
** client_handler.c
** File description:
** Client handler function callback.
*/

#include "logger.h"
#include "generic_list.h"
#include "client_commands.h"

int client_cmp(const void *entry, const void *id)
{
    const client_t *client = entry;
    int rhs = *((size_t *) id);

    return client->id == rhs;
}

void handle_protocol(client_t *client, server_t *server)
{
    char team_name[100] = {0};
    int free_space = -1;

    dprintf(client->id, "WELCOME\n");
    read(client->id, &team_name, 100);
    free_space = add_client_to_team(server, client, team_name);
    dprintf(client->id, "%d\n", free_space - 1);
}

int on_connect_client(int socket, void *data)
{
    server_t *server = (server_t *) data;
    client_t *client = client_create(socket);

    debugl("Client connect handler.\n");
    client->id = socket;
    handle_protocol(client, server);
    insert_head_list(server->clients, (void *) client);
    return 0;
}

int on_delete_client(int socket, void *data)
{
    server_t *server = (server_t *) data;
    client_t *client = NULL;
    team_t *team = NULL;

    debugl("Client delete handler.\n");
    client = pop_cmp_list( server->clients, client_cmp, (void *) &socket);
    if (!client) {
        errorl("Client %d not found.\n", socket);
        return 84;
    }
    infol("Deleting client %d.\n", client->id);
    team = get_client_team(client, server);
    remove_client_from_team(team, client, server);
    client_delete(client);
    return 0;
}

int on_active_client(int socket, void *data)
{
    char buffer[1025] = {0};
    size_t bytes_read = read(socket, buffer, 1024);
    client_t *client = NULL;
    server_t *server = (server_t *) data;

    if (bytes_read == 0)
        return -1;
    client = get_cmp_list(server->clients, client_cmp, (void *) &socket);
    if (client == NULL) {
        errorl("Client with socket: %d not found.\n", socket);
        return -1;
    }
    add_command(client, strdup(buffer));
    debugl("Client active handler.\n");
    return 0;
}
