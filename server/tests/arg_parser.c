/*
** EPITECH PROJECT, 2019
** arg_parser.c
** File description:
** Argument parser unit test.
*/

#include <string.h>
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "options.h"

int setup_args(const char *arguments, char ***data)
{
    int i = 0;
    char **ret;
    char *tmp = NULL;
    char *token = strdup(arguments);
    char *test = token;

    for (i = 0; test[i]; test[i] == ',' ? i++ : *test++);
    ret = malloc(sizeof(char *) * (i + 2));
    tmp = strtok(token, ",");
    i = 0;
    while (tmp) {
        ret[i] = strdup(tmp);
        tmp = strtok(NULL, ",");
        i++;
    }
    ret[i] = 0;
    *data = ret;
    return i;
}

Test(args, test_setup_args) {
    char **argv = NULL;
    int argc = setup_args("1,2,3,4,5", &argv);

    cr_assert(argc == 5);
    cr_assert(strcmp(argv[0], "1") == 0);
    cr_assert(strcmp(argv[1], "2") == 0);
    cr_assert(strcmp(argv[2], "3") == 0);
    cr_assert(strcmp(argv[3], "4") == 0);
    cr_assert(strcmp(argv[4], "5") == 0);
    cr_assert(argv[5] == 0);
}

Test(args, create_opt) {
    char **argv = NULL;
    int argc = setup_args("binary_name,-p,1024,-x,1024,-y,1024,\
-n,123,321,543,153,-c,12,-f,1234", &argv);
    options_t *opt = create_opt(argc, argv);

    cr_assert(opt->width == 1024);
    cr_assert(opt->height == 1024);
    cr_assert(strcmp(opt->name[0], "123") == 0);
    cr_assert(strcmp(opt->name[1], "321") == 0);
    cr_assert(strcmp(opt->name[2], "543") == 0);
    cr_assert(strcmp(opt->name[3], "153") == 0);
    cr_assert(opt->client_nb == 12);
    cr_assert(opt->freq == 1234);
    cr_assert(opt->port == 1024);
}

Test(args, basic_without) {
}
