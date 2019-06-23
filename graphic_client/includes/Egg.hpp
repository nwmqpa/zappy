/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Egg
*/

class Egg {

    public:

        Egg(unsigned int num, int x, int y);

        unsigned int getEggNum() const { return eggNum; }
        int getPosX() const { return x; }
        int getPosY() const { return y; }

    private:
        unsigned int eggNum;
        int x;
        int y;

};