//
// Created by Lyosha12 on 08.03.2019.
//

#ifndef FUSEGAME_LINEARDEATH_HPP
#define FUSEGAME_LINEARDEATH_HPP

#include <chrono>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../../Utility/Time/Stopwatch.hpp"

class LinearDeath {
  public:
    LinearDeath(std::chrono::milliseconds death_time);
    
    void startDie();
    
    intmax_t calcNewTransparency();
    bool continueDying(sf::Sprite& sprite);
    bool continueDying(sf::Text& text);
    
    
    size_t deathTime() const;
    size_t passedTime() const;
    bool isDying() const;
    bool isDied() const;
  
  private:
    Stopwatch<> stopwatch;
    std::chrono::milliseconds death_time;
    sf::Uint8 transparency = 255;
};


#endif // FUSEGAME_LINEARDEATH_HPP
