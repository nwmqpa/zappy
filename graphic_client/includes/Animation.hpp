/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#ifndef ANIMATIONS_HPP_
    #define ANIMATIONS_HPP_

#include <iostream>
#include <string>

class Animation {
    public:
        Animation();
        ~Animation();

        void continue_anim();
        void end_anim();
    private:
        std::string _path;
        int picture_in_line;
        int lines;
        int maxpicture;
};

#endif
