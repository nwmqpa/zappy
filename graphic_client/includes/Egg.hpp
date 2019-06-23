/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Egg
*/

#include <SDL2/SDL.h>

class Egg {

    public:

        Egg(unsigned int num, int x, int y, SDL_Texture *texture, int width, int height);

        unsigned int getEggNum() const { return eggNum; }
        int getPosX() const { return x; }
        int getPosY() const { return y; }
        SDL_Texture *getTexture() const { return texture; }
        int getWidth() const { return width; }
        int getHeight() const { return height; }

    private:
        SDL_Texture *texture;
        unsigned int eggNum;
        int x;
        int y;
        int width;
        int height;

};