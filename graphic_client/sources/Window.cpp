/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** GraphicalClient
*/

#include "Window.hpp"
#include <iostream>

Window::Window(std::string& name, int x, int y)
    : name(name)
{
#ifdef __SWITCH__
    if (initSDL(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
#else
    if (initSDL()) {
#endif
#ifdef __SWITCH__
        SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);
#else
        window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_RESIZABLE);
#endif
        if (window == nullptr)
            throw GraphicalException("Window error", "SDL_CreateWindow");
#ifndef __SWITCH__
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#endif
        if (renderer == nullptr)
            throw GraphicalException("Renderer error", "SDL_CreateRenderer");
        SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255);
        camera = { 0, 0, 0, 0 };
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

bool Window::initSDL(Uint32 sdl)
{
    if (SDL_Init(sdl) < 0) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Window::setCameraSize(int w, int h)
{
    camera.w = w;
    camera.h = h;
}

void Window::move(float x, float y)
{
    camera.x += x;
    camera.y += y;
}

void Window::renderIsoTexture(SDL_Texture *texture, int posX, int posY, int width, int height, int mapY, Camera camera)
{
    int w, h;
    SDL_Rect pos;
 
    SDL_GetWindowSize(window, &w, &h);
    pos.x = Isometry::getIsoX(posX, posY, width, height, w, h, camera);
    pos.y = Isometry::getIsoY(posX, posY, width, height, w, h, mapY, camera);
    pos.h = Isometry::getIsoHeight(height, camera);
    pos.w = Isometry::getIsoWidth(width, camera);
    if (SDL_RenderCopy(renderer, texture, nullptr, &pos) < 0)
        throw GraphicalException("Render copy error", "SDL_RenderCopy");
}

void Window::renderPlayer(GameState& state, int y)
{
    for (auto player : state.playerList) {
        this->renderIsoTexture(
            player->getTmp(),
            player->getX(),
            player->getY(),
            player->getWidth(),
            player->getHeight(),
            y,
            state.camera
        );
    }
}

void Window::renderEgg(GameState &state, int y)
{
    for (auto egg : state.eggs) {
        this->renderIsoTexture(
            egg->getTexture(),
            egg->getPosX(),
            egg->getPosY(),
            egg->getWidth(),
            egg->getHeight(),
            y,
            state.camera
        );
    }
}

void Window::renderTile(GameState &state, int y)
{
    for (auto tile : state.tileList) {
        if (tile->getTileInfo() == nullptr)
            continue;
        this->renderIsoTexture(
            tile->getTexture(),
            tile->getPosX(),
            tile->getPosY(),
            tile->getWidth(),
            tile->getHeight(),
            y,
            state.camera
        );
    }
}

void Window::renderResources(GameState &state, int y)
{
    auto food = state.resourcesManager.getResource("food");
    auto deraumere = state.resourcesManager.getResource("deraumere");
    auto linemate = state.resourcesManager.getResource("linemate");
    auto mendiane = state.resourcesManager.getResource("mendiane");
    auto sibur = state.resourcesManager.getResource("sibur");
    auto thystame = state.resourcesManager.getResource("thystame");

    for (auto tile : state.tileList) {
        if (tile->getTileInfo() == nullptr)
            continue;
        if (tile->hasFood()) {
            this->renderIsoTexture(
                std::get<0>(food),
                tile->getPosX(),
                tile->getPosY(),
                tile->getWidth(),
                tile->getHeight(),
                y,
                state.camera
            );
        }
        if (tile->hasLinemate()) {
            this->renderIsoTexture(
                std::get<0>(linemate),
                tile->getPosX(),
                tile->getPosY(),
                tile->getWidth(),
                tile->getHeight(),
                y,
                state.camera
            );
        }
        if (tile->hasThystame()) {
            this->renderIsoTexture(
                std::get<0>(thystame),
                tile->getPosX(),
                tile->getPosY(),
                tile->getWidth(),
                tile->getHeight(),
                y,
                state.camera
            );
        }
        if (tile->hasSibur()) {
            this->renderIsoTexture(
                std::get<0>(sibur),
                tile->getPosX(),
                tile->getPosY(),
                tile->getWidth(),
                tile->getHeight(),
                y,
                state.camera
            );
        }
        if (tile->hasDeraumere()) {
            this->renderIsoTexture(
                std::get<0>(deraumere),
                tile->getPosX(),
                tile->getPosY(),
                tile->getWidth(),
                tile->getHeight(),
                y,
                state.camera
            );
        }
        if (tile->hasMendiane()) {
            this->renderIsoTexture(
                std::get<0>(mendiane),
                tile->getPosX(),
                tile->getPosY(),
                tile->getWidth(),
                tile->getHeight(),
                y,
                state.camera
            );
        }
    }
}


void Window::render(GameState& state, int y)
{
    SDL_RenderClear(renderer);
    this->renderTile(state, y);
    this->renderPlayer(state, y);
    this->renderEgg(state, y);
    this->renderResources(state, y);
    SDL_RenderPresent(renderer);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
