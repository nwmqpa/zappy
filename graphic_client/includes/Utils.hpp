/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Utilities
*/

#include <tuple>
#include <vector>

template <typename T, typename U>
U getValueForIndex(const T index, const std::vector<std::tuple<T, U>> tuples)
{
    for (auto tuple : tuples) {
        if (index == std::get<0>(tuple))
            return std::get<1>(tuple);
    }
    return std::get<1>(tuples.at(0));
}

template <typename T, typename U>
T getIndexForValue(const U index, const std::vector<std::tuple<T, U>> tuples)
{
    for (auto tuple : tuples) {
        if (index == std::get<1>(tuple))
            return std::get<0>(tuple);
    }
    return std::get<0>(tuples.at(0));
}