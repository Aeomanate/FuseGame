//
// Created by Lyosha12 on 07.03.2019.
//

#ifndef FUSEGAME_CIRCLE_HPP
#define FUSEGAME_CIRCLE_HPP

#include <SFML/System/Vector2.hpp>
#include "../Line/Line.hpp"

struct Circle {
    Circle(float R, sf::Vector2f position);
    
    struct Intersection {
        Intersection(int count, sf::Vector2f A = { }, sf::Vector2f B = { });
        bool isExists() const;
        
        
        int const count;
        sf::Vector2f const A, B;
    };
    Intersection intersection(Circle const& other) const;
    Intersection intersection(Line const& line) const;
    bool isInside(sf::Vector2f point) const;
    
    float R;
    sf::Vector2f position;
};

#endif //FUSEGAME_CIRCLE_HPP
