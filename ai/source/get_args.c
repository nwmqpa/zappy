/*
** EPITECH PROJECT, 2018
** zappy_ai
** File description:
** get arguments
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

#include "my_ai.h"

void print_help(unsigned int exit_value)
{
    printf("USAGE: ./zappy_ai -p port -n name -h machine\n"
    "   port    is the port number\n"
    "   name    is the name of the team\n"
    "   machine is the name of the machine; localhost by default\n");
    exit(exit_value);
}

/*
** exit if hostname is invalid
** printf("Name: %s\n", hstnm->h_name);
*/
void get_host_name(char *hostname)
{
    struct hostent *hstnm = gethostbyname(hostname);

    if (!hstnm) {
        printf("No such hostname: '%s'\n", hostname);
        exit(84);
    }
}

void get_args(int ac, char **av, arguments_t *args)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        print_help(0);
    } else if (ac != 7)
        print_help(84);
    if (get_opt(ac, av, args) == 84) {
        printf("Problem while getting options\n");
        exit(84);
    }
    if (strcmp(args->machine, "localhost") == 0) {
        free(args->machine);
        args->machine = strdup("127.0.0.1");
    }
    get_host_name(args->machine);
}