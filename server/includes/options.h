/*
** EPITECH PROJECT, 2019
** options.h
** File description:
** header of the option struct and functions.
*/

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BREAK(x) (x); break

/// Option struct that handle server parameters.
typedef struct options_s {
    short port;
    int width;
    int height;
    char **name;
    int client_nb;
    int freq;
} options_t;

options_t *create_opt(int argc, char *argv[]);
int check_opt(options_t *options);
void print_opt(options_t *options);

#endif /* OPTIONS_H_ */
