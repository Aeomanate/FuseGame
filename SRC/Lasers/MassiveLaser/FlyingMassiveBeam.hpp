//
// Created by Lyosha12 on 03.03.2019.
//

#ifndef FUSEGAME_FLYINGBEAM_HPP
#define FUSEGAME_FLYINGBEAM_HPP

#include "../../Utility/MemoryTextureStorage/MemoryTextureStorage.hpp"
#include "../../Utility/GameObject.hpp"
#include "../../Utility/ProgramEvents/ProgramEvents.hpp"
#include "../../Utility/Resources/Resources.hpp"
#include "../../Utility/Math/Math.hpp"
#include "../../Animations/Explosion/Explosion.hpp"
#include "../../Animations/FrameByFrame/FrameByFrame.hpp"
#include "../../Utility/MovementBorders.hpp"

class FlyingMassiveBeam: public GameObject {
  public:
    FlyingMassiveBeam(
        sf::Vector2f position,
        sf::Vector2f direction,
        sf::Vector2f target_position,
        sf::Vector2f speed,
        float massive_explosion_scale,
        MassiveExplosion::DamageCalculator damage_calculator,
        MovementBorders movement_borders
    );
    
    ProgramEvents update() override;
    void notify(ProgramEvent) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
  public:
    FrameByFrame massive_beam_animation;
    
    sf::Vector2f position, direction;
    sf::Vector2f target_position;
    
    sf::Vector2f speed;
    Timer<> move_fly_interval = 10ms;
    
    float massive_explosion_scale;
    MassiveExplosion::DamageCalculator damage_calculator;
    MovementBorders movement_borders;
};


#endif //FUSEGAME_FLYINGBEAM_HPP
