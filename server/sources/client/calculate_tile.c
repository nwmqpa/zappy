/*
** EPITECH PROJECT, 2019
** calculate_tile.c
** File description:
** Calculate tile file.
*/

#include <math.h>
#include <stdint.h>
#include "client_commands.h"

float distance(int sx, int sy, int cx, int cy)
{
    return sqrt(pow(abs(cx - cy), 2) + pow(abs(cx - cy), 2));
}

static pos_t real_s_tile(uint32_t w, uint32_t h, pos_t s, pos_t c)
{
    float min = w * h;
    int index = 0;
    pos_distance_t distances[] = {
        {{s.x, s.y}, distance(s.x, s.y, c.x, c.y)},
        {{s.x, s.y + h}, distance(s.x, s.y + h, c.x, c.y)},
        {{s.x - w, s.y + h}, distance(s.x - w, s.y + h, c.x, c.y)},
        {{s.x - w, s.y}, distance(s.x - w, s.y, c.x, c.y)},
        {{s.x - w, s.y - h}, distance(s.x - w, s.y - h, c.x, c.y)},
        {{s.x, s.y - h}, distance(s.x, s.y - h, c.x, c.y)},
        {{s.x + w, s.y - h}, distance(s.x + w, s.y - h, c.x, c.y)},
        {{s.x + w, s.y}, distance(s.x + w, s.y, c.x, c.y)},
        {{s.x + w, s.y + h}, distance(s.x + w, s.y + h, c.x, c.y)}
    };
    for (int i = 0; i < 9; i++) {
        if (distances[i].distance < min) {
            index = i;
            min = distances[i].distance;
        }
    }
    return distances[index].pos;
}

int calculate_tile(server_t *server, pos_t s, pos_t c)
{
    double degrees = 0.0;
    pos_t rs = real_s_tile(server->width, server->height, s, c);

    if (rs.x == c.x)
        return (rs.y < 0 ? 6 : 1);
    degrees = (atan((c.y - rs.y) / (c.x - rs.x)) * 180.0) / M_PI;
    return ceil((degrees - 22.5) / 45);
}
