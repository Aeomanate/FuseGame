//
// Created by Lyosha12 on 07.03.2019.
//

#ifndef FUSEGAME_HITPOINTSDECREASE_HPP
#define FUSEGAME_HITPOINTSDECREASE_HPP

#include <sstream>
#include <iomanip>
#include "../../Utility/Math/Math.hpp"
#include "../../Utility/ProgramEvents/ProgramEvents.hpp"
#include "../../Utility/GameObject.hpp"
#include "../../Utility/IndexDataFile/IndexDataFile.hpp"
#include "../../Utility/Time/Timer.hpp"
#include "../../Utility/Resources/Resources.hpp"

class HitpointsDecrease: public GameObject {
  public:
    HitpointsDecrease(float value, sf::Vector2f position, sf::Color color);
    
    ProgramEvents update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void notify(ProgramEvent e) override;
    
    void updateTextPosition();
    
  private:
    sf::Vector2f start_position, cur_position, end_position, direction;
    sf::Font font;
    sf::Text text;
    
    Parabola text_trajectory;
    Timer<> move_timer = 20ms;
};


#endif // FUSEGAME_HITPOINTSDECREASE_HPP
