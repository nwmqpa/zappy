/*
** EPITECH PROJECT, 2019
** client_command.c
** File description:
** test file.
*/

#include <criterion/criterion.h>
#include "client_commands.h"

client_t *create_client_add_command(int how_many) {
    client_t *client = client_create(0);
    char *str = NULL;

    for (int i = 0; i < how_many; ++i) {
        asprintf(&str, "test %d", i);
        add_command(client, str);
        str = NULL;
    }
    return client;
}

Test(client_command, pushing_command) {
    client_t *client = create_client_add_command(1);
    cr_expect(len_list(client->commands) == 1, "Should be 1.");

    char *command = get_list(client->commands, 0);

    cr_expect(strcmp(command, "test 0") == 0, "Should be 'test 0' It's %s\n", command);
}

Test(client_command, processing_command) {
    client_t *client = create_client_add_command(5);
    server_t *server = NULL;

    prepare_command(client);
    process_command(client, server);
    prepare_command(client);
    process_command(client, server);
    cr_assert(len_list(client->commands) == 3);
}

Test(client_command, too_much_command) {
    client_t *client = create_client_add_command(20);
    char *command = get_list(client->commands, 0);
    server_t *server = NULL;

    cr_assert(len_list(client->commands) == 10);
    cr_assert(strcmp(command, "test 9") == 0, "Should be test 9 it's %s\n", command);
    prepare_command(client);
    process_command(client, server);
    command = get_list(client->commands, 0);
    cr_assert(len_list(client->commands) == 9);
    cr_assert(strcmp(command, "test 8") == 0, "Should be test 8 it's %s\n", command);
}
