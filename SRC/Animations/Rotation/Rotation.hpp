//
// Created by Lyosha12 on 26.02.2019.
//

#ifndef FUSEGAME_ANIMETIONROTARY_HPP
#define FUSEGAME_ANIMETIONROTARY_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "../../Utility/Time/Timer.hpp"
#include "../../Utility/Updateable.hpp"

class Rotation: public Updateable, public sf::Drawable {
  public:
    enum class Direction {
        Clockwise = 1,
        Anticlockwise = -1
    };
    
    ProgramEvents update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  
  public:
    Rotation(
        sf::Sprite sprite,
        Direction direction,
        float degree_per_interval,
        Timer<> timer
    );
    
    void changeDegree(float new_degree);
    void changeDirection(Direction new_direction);
  
  private:
    sf::Sprite sprite;
    Direction direction;
    float degree_per_interval;
    Timer<> timer;
};


#endif //FUSEGAME_ANIMETIONROTARY_HPP
