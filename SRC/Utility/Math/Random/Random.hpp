//
// Created by Lyosha12 on 07.03.2019.
//

#ifndef FUSEGAME_RANDOM_HPP
#define FUSEGAME_RANDOM_HPP

#include <random>
#include <chrono>

extern std::mt19937 random;

template <class T, class U, class Common = std::common_type_t<T, U>>
Common specRandom(Common begin, Common end) {
    if constexpr(std::is_floating_point<Common>()) {
        std::uniform_real_distribution<Common> distribution(begin, end);
        return distribution(random);
    } else {
        std::uniform_int_distribution<Common> distribution(begin, end);
        return distribution(random);
    }
}

template <class T>
T specRandom(T begin, T end) {
    return specRandom<T, T> (begin, end);
}

#endif // FUSEGAME_RANDOM_HPP
