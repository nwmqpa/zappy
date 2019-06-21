/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include "Player.hpp"

Player::Player(std::string &path, SDL_Renderer *render)
{
    sprite = SDL_LoadBMP(path.c_str());
    if (sprite == nullptr)
        throw GraphicalException("BMP loading error on Player", "SDL_LoadBMP Player");
    tmp = SDL_CreateTextureFromSurface(render, sprite);
    if (tmp == nullptr)
        throw GraphicalException("Buffering texture creation error",
                "SDL_CreateTextureFromSurface");
    texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, sprite->w, sprite->h);
    if (texture == nullptr)
        throw GraphicalException("Texture creation error", "SDL_CreateTexture");
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
