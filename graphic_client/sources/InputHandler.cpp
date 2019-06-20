/*
** EPITECH PROJECT, 2019
** InputHandler.cpp
** File description:
** Header file of Input Handler class.
*/

#include "InputHandler.hpp"

void InputHandler::handle(const WindowCreator &window, InputHandler::InputDatas &inputs) const noexcept {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_JOYBUTTONDOWN:
            if (event.jbutton.which == 0)
                if (event.jbutton.button == 10)
                    inputs.should_quit = true;
            break;
        case SDL_FINGERMOTION:
            inputs.pos[0] = event.tfinger.x;
            inputs.pos[1] = event.tfinger.y;
            break;
        case SDL_KEYDOWN:
            setKeys(event, inputs);
            break;
        case SDL_JOYAXISMOTION:
            if (event.jbutton.which == 0) {
                inputs.x = event.jball.xrel;
                inputs.y = event.jball.yrel;
            } else {
                inputs.zoom = event.jball.yrel;
            }
            break;
        case SDL_MOUSEMOTION:
            inputs.pos[0] = event.motion.x;
            inputs.pos[1] = event.motion.y;
            break;
        default:
            std::cout << "[No input]" << std::endl;
        }
    }
}

void InputHandler::setKeys(SDL_Event &event, InputHandler::InputDatas &inputs) const noexcept {
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            inputs.should_quit = true;
            break;
        case SDLK_UP:
            inputs.y = 1.0;
            break;
        case SDLK_DOWN:
            inputs.y = -1.0;
            break;
        case SDLK_LEFT:
            inputs.x = -1.0;
            break;
        case SDLK_RIGHT:
            inputs.x = 1.0;
            break;
        case SDLK_PLUS:
            inputs.zoom = 1.0;
            break;
        case SDLK_MINUS:
            inputs.zoom = -1.0;
            break;
        default:
            inputs.x = 0;
            inputs.y = 0;
            inputs.zoom =0;
    }
}