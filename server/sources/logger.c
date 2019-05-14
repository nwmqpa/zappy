/*
** EPITECH PROJECT, 2019
** logger.c
** File description:
** logger code file.
*/

#include "logger.h"

// The log const is defining how the log is shown.
//                        [Date - hour | level] message
static const char *LOG = "[%s | %s] %s";

static const char *LEVEL_NAME[] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG"};

char *get_log(int log_level, const char *str)
{
    char *ret = NULL;
    time_t epoch = time(NULL);
    char *time_str = ctime(&epoch);

    time_str[24] = 0;
    asprintf(&ret, LOG, time_str, LEVEL_NAME[log_level], str);
    return ret;
}

int get_log_level()
{
    char *env_level = getenv("LOG_LEVEL");

    if (env_level)
        return atoi(env_level);
    return LOG_LEVEL;
}

void fatall(const char *str, ...)
{
    int log_level = get_log_level();
    char *log = get_log(FATAL_LOG, str);

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
    char *log = get_log(ERROR_LOG, str);

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
    char *log = get_log(FATAL_LOG, str);

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
    char *log = get_log(INFO_LOG, str);

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
    char *log = get_log(INFO_LOG, str);

    if (log_level >= DEBUG_LOG) {
        va_list ap;
        va_start(ap, str);
        vfprintf(stderr, log, ap);
        va_end(ap);
        free(log);
    }
}
