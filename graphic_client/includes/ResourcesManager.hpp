/*
** EPITECH PROJECT, 2018
** ResourcesManager.hpp
** File description:
** Handle resources.
*/

#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <map>

template <typename T, typename U>
class ResourcesManager {

    typedef T *(*opener) (std::string path, U data);

public:

    ResourcesManager(opener func)
        : _func(func)
        , _datas()
    {}

    ~ResourcesManager() = default;

    void addResource(std::string path, std::string name, U data)
    {
        T *entry = _func(path, data);
        _datas.insert({name, entry});
    }

    T *getResource(std::string name)
    {
        return _datas.at(name);
    }

private:
    opener _func;
    std::map<std::string, T *> _datas;
};