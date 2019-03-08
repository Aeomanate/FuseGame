//
// Created by Lyosha12 on 02.03.2019.
//

#ifndef FUSEGAME_STATSDATA_HPP
#define FUSEGAME_STATSDATA_HPP

#include "../Utility/Time/Stopwatch.hpp"

struct StatsData {
    size_t enemies_killed = 0;
    Stopwatch<> player_lifetime;
};

#endif //FUSEGAME_STATSDATA_HPP
