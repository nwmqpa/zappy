/*
** EPITECH PROJECT, 2018
** zappy_ai
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

#include "my_ai.h"

void free_all(arguments_t *args)
{
    free(args->name);
    free(args->machine);
    free(args);
}

/*
** main
** printf("port    ==> %s\n", args_t->target);
** printf("name    ==> %d\n", args_t->port);
** printf("machine ==> %s\n\n", args_t->password);
*/
int main(int ac, char **av)
{
    arguments_t *args = calloc(sizeof(arguments_t), 1);

    get_args(ac, av, args);

    printf("port    ==> %d\n", args->port);
    printf("name    ==> %s\n", args->name);
    printf("machine ==> %s\n", args->machine);
    return (0);
}