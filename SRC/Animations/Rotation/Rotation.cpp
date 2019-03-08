// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 26.02.2019.
//

#include <SFML/Graphics/RenderTarget.hpp>
#include "Rotation.hpp"


Rotation::Rotation(
    sf::Sprite sprite,
    Direction direction,
    float degree_per_interval,
    Timer<> timer
)
: sprite(sprite)
, direction(direction)
, degree_per_interval(degree_per_interval)
, timer(timer)
{ }

ProgramEvents Rotation::update() {
    if(!timer.resetCheckIntervalExpired()) {
        return { };
    }
    
    sprite.rotate(static_cast<int>(direction)*degree_per_interval);
    
    return { };
}

void Rotation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}


void Rotation::changeDegree(float new_degree) {
    degree_per_interval = new_degree;
}
void Rotation::changeDirection(Direction new_direction) {
    direction = new_direction;
}