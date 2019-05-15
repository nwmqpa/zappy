/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main file of the zappy server.
*/

#include "options.h"
#include "zappy.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    options_t *options = create_opt(argc, argv);
    int listener = 0;

    print_opt(options);
    if (check_opt(options) == -1) {
        errorl("Error in argument parsing.\n");
        return 84;
    }
    listener = create_listener(options);
    setup_server();
    zappy_server(options);
    return 0;
}