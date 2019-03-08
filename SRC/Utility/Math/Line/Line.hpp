//
// Created by Lyosha12 on 07.03.2019.
//

#ifndef FUSEGAME_LINE_HPP
#define FUSEGAME_LINE_HPP

#include <SFML/System/Vector2.hpp>

struct Line {
    Line(float A, float B, float C);
    Line(sf::Vector2f p1, sf::Vector2f p2);
    float ordinate(float abscissa) const;
    
    float distance(sf::Vector2f point) const;
    float A, B, C;
};

#endif //FUSEGAME_LINE_HPP
