// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 07.03.2019.
//

#include "Random.hpp"

std::mt19937 random {static_cast<unsigned>(
    std::chrono::system_clock::now().time_since_epoch().count()
)};