/*
** EPITECH PROJECT, 2019
** client_command.c
** File description:
** test file.
*/

#include <criterion/criterion.h>
#include "client.h"

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
    cr_expect(len_command(client) == 1, "Should be 1.");

    char *command = get_list(client->commands, 0);

    cr_expect(strcmp(command, "test 0") == 0, "Should be 'test 0' It's %s\n", command);
}

Test(client_command, processing_command) {
    client_t *client = create_client_add_command(5);

    process_command(client);
    process_command(client);
    cr_assert(len_command(client) == 3);
}

Test(client_command, too_much_command) {
    client_t *client = create_client_add_command(20);
    char *command = get_list(client->commands, 0);

    cr_assert(len_command(client) == 10);
    cr_assert(strcmp(command, "test 9") == 0, "Should be test 9 it's %s\n", command);
    process_command(client);
    command = get_list(client->commands, 0);
    cr_assert(len_command(client) == 9);
    cr_assert(strcmp(command, "test 8") == 0, "Should be test 8 it's %s\n", command);
}
