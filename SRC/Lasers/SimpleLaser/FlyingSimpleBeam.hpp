//
// Created by Lyosha12 on 06.03.2019.
//

#ifndef FUSEGAME_FLYINGSIMPLEBEAM_HPP
#define FUSEGAME_FLYINGSIMPLEBEAM_HPP

#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>
#include "../../Utility/ProgramEvents/ProgramEvents.hpp"
#include "../../Utility/GameObject.hpp"
#include "../../Utility/Time/Timer.hpp"
#include "../../Utility/MemoryTextureStorage/MemoryTextureStorage.hpp"
#include "../../Animations/FrameByFrame/FrameByFrame.hpp"
#include "../../Utility/Math/Math.hpp"
#include "../../Animations/Explosion/Explosion.hpp"
#include "../../Utility/WindowForTests/WindowForTests.hpp"
#include "../../Utility/MovementBorders.hpp"

class FlyingSimpleBeam: public GameObject {
  public:
    FlyingSimpleBeam(
        sf::Vector2f position,
        sf::Vector2f direction,
        float damage,
        MovementBorders movement_borders
    );
    
    
    ProgramEvents update() override;
    void notify(ProgramEvent e) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
  private:
    ProgramEvents handleHit(size_t beam_id);
  
  private:
    FrameByFrame simple_beam_animation;
    sf::Vector2f position;
    sf::Vector2f direction;
    float damage;
    
    sf::Vector2f speed = { 12, 12 };
    Timer<> move_fly_interval = 15ms;
    
    MovementBorders movement_borders;
};


#endif // FUSEGAME_FLYINGSIMPLEBEAM_HPP
