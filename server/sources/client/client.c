/*
** EPITECH PROJECT, 2019
** client.c
** File description:
** main client file.
*/

#include "logger.h"
#include "client_commands.h"

void move_client(client_t *client, int x, int y, pos_t size)
{
    client->position.x += x;
    client->position.y += y;

    client->position.x %= size.x;
    client->position.y %= size.y;

    if (client->position.x < 0)
        client->position.x = (size.x - x) % size.x;
    if (client->position.y < 0)
        client->position.y = (size.y - y) % size.y;
}

client_t *client_create(size_t id)
{
    client_t *new = calloc(sizeof(client_t), 1);

    new->commands = create_list();
    new->id = id;
    new->inventory.inv.food = 10;
    new->level = 1;
    return new;
}

void print_client(const client_t *client)
{
    printf("Client {"
            "   id: %ld\n"
            "}\n"
            , client->id);
}

void print_client_list(const void *data)
{
    print_client((client_t *) data);
}
