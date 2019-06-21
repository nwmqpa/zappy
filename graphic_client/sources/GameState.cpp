/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GameState
*/

#include "GameState.hpp"

GameState::GameState(std::string ip, short int port)
 : lastData(nullptr)
 , tileList()
 , protocol(ip, port)
{
    this->camera.center.x = 0;
    this->camera.center.y = 0;
    this->camera.scale.x = 2;
    this->camera.scale.y = 2;
}
