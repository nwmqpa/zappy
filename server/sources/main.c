/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main file of the zappy server.
*/

#include "options.h"
#include "zappy.h"
#include "logger.h"
#include "server.h"

int main(int argc, char *argv[])
{
    options_t *options = create_opt(argc, argv);
    server_t *server = NULL;
    int listener = 0;

    if (check_opt(options) == -1) {
        errorl("Error in argument parsing.\n");
        free(options);
        return 84;
    }
    listener = create_listener(options);
    if (listener == -1) {
        free(options);
        return 84;
    }
    server = setup_server(options);
    if (!server) {
        free(options);
        return 84;
    }
    return zappy_server(server);
}
