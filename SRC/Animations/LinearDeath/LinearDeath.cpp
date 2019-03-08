// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 08.03.2019.
//

#include "LinearDeath.hpp"

LinearDeath::LinearDeath(std::chrono::milliseconds death_time)
: death_time(death_time)
{ }

void LinearDeath::startDie() {
    if(!stopwatch.isEnable()) {
        stopwatch.start();
    } else {
        throw std::logic_error("Try to restart death timer");
    }
}


intmax_t LinearDeath::calcNewTransparency() {
    size_t ms_passed = stopwatch.getCount<std::chrono::milliseconds, size_t>();
    
    intmax_t new_transparency = transparency - static_cast<intmax_t>(
        255 * ms_passed / static_cast<float>(death_time.count())
    );
    
    return new_transparency;
}
bool LinearDeath::continueDying(sf::Sprite& sprite) {
    auto new_transparency = calcNewTransparency();
    
    if(new_transparency < 0) {
        return false;
    }
    
    sprite.setColor({0, 0, 0, transparency});
    
    return (transparency = static_cast<sf::Uint8>(new_transparency)) > 0;
}
bool LinearDeath::continueDying(sf::Text& text) {
    auto new_transparency = calcNewTransparency();
    
    if(new_transparency < 0) {
        return false;
    }
    
    sf::Color fill_color = text.getFillColor();
    sf::Color outline_color = text.getOutlineColor();
    
    fill_color.a = transparency;
    outline_color.a = transparency;
    
    text.setFillColor(fill_color);
    text.setOutlineColor(outline_color);
    
    return true;
}


size_t LinearDeath::deathTime() const {
    return static_cast<size_t>(death_time.count());
}
size_t LinearDeath::passedTime() const {
    return stopwatch.getCount<std::chrono::milliseconds, size_t>();
}
bool LinearDeath::isDying() const {
    return stopwatch.isEnable();
}
bool LinearDeath::isDied() const {
    return stopwatch.getInterval<std::chrono::milliseconds>() >= death_time;
}