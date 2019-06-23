/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Egg
*/

#include "Player.hpp"
#include <string>

class Team {

    public:

        Team(const char name[128]);

        std::string getName() const { return name; }
        std::vector<Player *> &getPlayers() { return players; }

    private:
        std::vector<Player *> players;
        std::string name;

};