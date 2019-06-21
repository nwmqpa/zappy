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
}
