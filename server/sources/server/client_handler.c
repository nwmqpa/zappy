/*
** EPITECH PROJECT, 2019
** client_handler.c
** File description:
** Client handler function callback.
*/

#include "server.h"
#include "client.h"
#include "logger.h"
#include "generic_list.h"

static int deleting_client_cmp(const void *id_checked, const void *id)
{
    size_t lhs = *((size_t *) id_checked);
    size_t rhs = *((size_t *) id);

    return lhs == rhs;
}

void handle_protocol(client_t *client, server_t *server)
{
    char team_name[100] = {0};
    int free_space = -1;

    dprintf(client->id, "WELCOME\n");
    read(client->id, &team_name, 100);
    free_space = add_client_to_team(server, client, team_name);
    dprintf(client->id, "%d\n", free_space);
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

    debugl("Client delete handler.\n");
    client = pop_cmp_list(
            server->clients, deleting_client_cmp, (void *) &socket);
    infol("Deleting client %d.", client->id);
    // TODO: Delete client.
    return 0;
}

int on_active_client(int socket, void *data)
{
    char buffer[1025];
    size_t bytes_read = read(socket, buffer, 1024);

    if (bytes_read == 0)
        return -1;
    debugl("Client active handler.\n");
    return 0;
}