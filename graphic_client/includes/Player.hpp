/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Exception.hpp"
#include "SDL2/SDL.h"
#include "protocols.h"
#include <vector>

class Player {
public:
    Player(SDL_Texture *texture, int height, int width);
    ~Player() = default;

    void setInventoryContent(std::vector<unsigned int> inventory);
    std::vector<unsigned int> getInventoryContent() { return inventory; }

    void setPosition(unsigned int x, unsigned int y);
    unsigned int getX() { return x; }
    unsigned int getY() { return y; }
    int getHeight() const noexcept { return height; }
    int getWidth() const noexcept { return width; }

    void setPlayerNum(unsigned int num);
    unsigned int getPlayerNum() { return player_num; }

    void setLevel(unsigned int level);
    unsigned int getLevel() { return level; }

    void setOrientation(ORIENTATION orientation);
    ORIENTATION getOrientation() { return orientation; }

    void setTeamName(std::string teamName);
    std::string getTeamName() { return teamName; }

    SDL_Texture* getTmp() { return texture; }

private:
    SDL_Texture *texture;

    unsigned int player_num;
    std::vector<unsigned int> inventory;
    unsigned int x;
    unsigned int y;
    unsigned int level;
    ORIENTATION orientation;
    std::string teamName;
    int height;
    int width;
};

#endif
