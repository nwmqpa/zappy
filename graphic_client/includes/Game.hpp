/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "GameState.hpp"
#include "InputHandler.hpp"
#include "Window.hpp"

class Game {
public:
    Game(std::string ip, int port);
    ~Game() = default;

    void life(Window&);
    void processData(Window&);
    void eventLoop(Window&, std::vector<Tile*>);
    void updateCamera(InputHandler::InputDatas& inputData);

private:

    void limitFramerate() noexcept;
    std::string ip;
    int port;
    GameState state;
    unsigned int endTime;
    unsigned int startTime;
    unsigned int delta;
    short fps;
    short timePerFrame;
};

#endif
