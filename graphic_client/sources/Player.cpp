/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Player.hpp"

Player::Player(SDL_Texture *texture, int height, int width)
    : texture(texture)
    , height(height)
    , width(width)
{
}

void Player::setInventoryContent(std::vector<unsigned int> inventory)
{
    this->inventory = inventory;
}

void Player::setPosition(unsigned int x, unsigned int y)
{
    this->x = x;
    this->y = y;
}

void Player::setPlayerNum(unsigned int num)
{
    this->player_num = num;
}

void Player::setOrientation(ORIENTATION orientation)
{
    this->orientation = orientation;
}

void Player::setTeamName(std::string teamName)
{
    this->teamName = teamName;
}

void Player::setLevel(unsigned int level)
{
    this->level = level;
}