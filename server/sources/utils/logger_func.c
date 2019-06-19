/*
** EPITECH PROJECT, 2019
** logger_func.c
** File description:
** function of logger.
*/

#include "logger.h"

void fatall(const char *str, ...)
{
    int log_level = get_log_level();
    char *log = get_log(FATAL_LOG, "\e[31m", str);

    if (log_level >= FATAL_LOG) {
        va_list ap;
        va_start(ap, str);
        vfprintf(stderr, log, ap);
        va_end(ap);
        free(log);
    }
}

void errorl(const char *str, ...)
{
    int log_level = get_log_level();
    char *log = get_log(ERROR_LOG, "\e[91m", str);

    if (log_level >= ERROR_LOG) {
        va_list ap;
        va_start(ap, str);
        vfprintf(stderr, log, ap);
        va_end(ap);
        free(log);
    }
}

void warnl(const char *str, ...)
{
    int log_level = get_log_level();
    char *log = get_log(WARN_LOG, "\e[33m", str);

    if (log_level >= WARN_LOG) {
        va_list ap;
        va_start(ap, str);
        vfprintf(stderr, log, ap);
        va_end(ap);
        free(log);
    }
}

void infol(const char *str, ...)
{
    int log_level = get_log_level();
    char *log = get_log(INFO_LOG, "\e[92m", str);

    if (log_level >= INFO_LOG) {
        va_list ap;
        va_start(ap, str);
        vfprintf(stderr, log, ap);
        va_end(ap);
        free(log);
    }
}

void debugl(const char *str, ...)
{
    int log_level = get_log_level();
    char *log = get_log(DEBUG_LOG, "\e[94m", str);

    if (log_level >= DEBUG_LOG) {
        va_list ap;
        va_start(ap, str);
        vfprintf(stderr, log, ap);
        va_end(ap);
        free(log);
    }
}
