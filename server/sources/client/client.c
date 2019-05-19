/*
** EPITECH PROJECT, 2019
** client.c
** File description:
** main client file.
*/

#include "client.h"

client_t *client_create(size_t id)
{
    client_t *new = calloc(sizeof(client_t), 1);

    new->commands = create_list();
    new->id = id;
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
