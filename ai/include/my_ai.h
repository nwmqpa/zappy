/*
** EPITECH PROJECT, 2018
** ai zappy
** File description:
** ai zappy
*/

#pragma once

#include <unistd.h>

typedef struct arguments_s {
    int port;
    char *name;
    char *machine;
} arguments_t;

void get_args(int ac, char **av, arguments_t *args);
int get_opt(int argc, char **argv, arguments_t *args);
void get_host_name(char *hostname);
void print_help(unsigned int exit_value);