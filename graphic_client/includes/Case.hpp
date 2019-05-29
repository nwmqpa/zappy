/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef CASE_HPP_
    #define CASE_HPP_

class Case {
    public:
        Case();
        ~Case();

        void update();

    private:
        SDL_Surface *_back;
        srv_tile_content_t *tile;
};

#endif
