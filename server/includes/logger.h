/*
** EPITECH PROJECT, 2019
** logger.h
** File description:
** logger one header library.
*/

#ifndef LOGGER_H_
#define LOGGER_H_

#ifndef LOG_LEVEL

/*
** 0 - Only fatal logs.
** 1 - error logs + previous.
** 2 - warn logs  + previous.
** 3 - info logs  + previous.
** 4 - debug logs + previous.
*/
#define LOG_LEVEL 2

#endif /* LOG_LEVEL */

#define FATAL_LOG 0
#define ERROR_LOG 1
#define WARN_LOG 2
#define INFO_LOG 3
#define DEBUG_LOG 4

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_log_level();

void fatall(const char *str, ...);

void errorl(const char *str, ...);

void warnl(const char *str, ...);

void infol(const char *str, ...);

void debugl(const char *str, ...);

#endif /* LOGGER_H_ */
