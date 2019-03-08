//
// Created by Lyosha12 on 08.03.2019.
//

#ifndef FUSEGAME_MOVEMENTBORDERS_HPP
#define FUSEGAME_MOVEMENTBORDERS_HPP

#include <SFML/System/Vector2.hpp>

struct MovementBorders {
    inline bool isIn(sf::Vector2f v) {
        return
            min.x <= v.x && v.x <= max.x &&
            min.y <= v.y && v.y <= max.y;
    }
    sf::Vector2f min, max;
};

#endif //FUSEGAME_MOVEMENTBORDERS_HPP
