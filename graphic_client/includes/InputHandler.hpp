/*
** EPITECH PROJECT, 2019
** InputHandler.hpp
** File description:
** Header file off Input Handler class.
*/

#pragma once

#include "Window.hpp"
#include <SDL2/SDL.h>
#include <iostream>

class InputHandler {
public:
    struct InputDatas {
        float x;
        float y;
        float zoom;
        bool should_quit = false;
        float pos[2];
    };

    InputHandler() = default;
    ~InputHandler() = default;

    void handle(const Window& window, InputDatas& inputs) const noexcept;

private:
    void setKeys(SDL_Event& events, InputHandler::InputDatas& inputs) const noexcept;
};