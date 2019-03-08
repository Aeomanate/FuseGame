//
// Created by Lyosha12 on 08.03.2019.
//

#ifndef FUSEGAME_MARCH8_HPP
#define FUSEGAME_MARCH8_HPP

#include "../Animations/FrameByFrame/FrameByFrame.hpp"
#include "../Utility/Resources/Resources.hpp"

class March8: public GameObject {
  public:
    March8(sf::Vector2u screen);
    
    ProgramEvents update() override;
    void notify(ProgramEvent e) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  
  private:
    sf::Font font;
    sf::Text march8_text;
    // FrameByFrame secret_animation;
  
    // bool is_secret_animation = false;
};


#endif // FUSEGAME_MARCH8_HPP
