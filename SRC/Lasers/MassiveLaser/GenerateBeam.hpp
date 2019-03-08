//
// Created by Lyosha12 on 03.03.2019.
//

#ifndef FUSEGAME_GENERATEBEAM_HPP
#define FUSEGAME_GENERATEBEAM_HPP

#include "../../Utility/MemoryTextureStorage/MemoryTextureStorage.hpp"
#include "../../Utility/GameObject.hpp"
#include "../../Utility/ProgramEvents/ProgramEvents.hpp"
#include "../../Utility/Math/Math.hpp"
#include "../../Animations/FrameByFrame/FrameByFrame.hpp"
#include "FlyingMassiveBeam.hpp"

class GenerateBeam: public GameObject {
  public:
    GenerateBeam(
        Circle const& player_circle,
        sf::Vector2f const& player_direction
    );
    
    ProgramEvents update() override;
    void notify(ProgramEvent) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  
  
  private:
    static const MemoryTextureStorage massive_beam_generate_sprite_sheet;
    FrameByFrame massive_beam_generated;
    Circle const& player_circle;
    sf::Vector2f const& player_direction;
};


#endif // FUSEGAME_GENERATEBEAM_HPP
