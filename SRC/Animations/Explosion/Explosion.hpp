//
// Created by Lyosha12 on 06.03.2019.
//

#ifndef FUSEGAME_EXPLOSION_HPP
#define FUSEGAME_EXPLOSION_HPP


#include <SFML/Audio.hpp>
#include "../../Utility/ProgramEvents/ProgramEvents.hpp"
#include "../../Utility/GameObject.hpp"
#include "../FrameByFrame/FrameByFrame.hpp"
#include "../../Utility/Time/Timer.hpp"
#include "../../Utility/Math/Math.hpp"
#include "../../Utility/Resources/Resources.hpp"

class Explosion: public GameObject {
  public:
    Explosion(
        FrameByFrame explosion,
        sf::Vector2f position,
        std::string sound_name,
        std::chrono::milliseconds explosion_delay = 0ms,
        float scale = 1
    );
    
    Explosion(
        size_t explosion_number,
        sf::Vector2f position,
        std::chrono::milliseconds explosion_delay = 0ms
    );
    
    ProgramEvents update() override;
    void notify(ProgramEvent) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
  private:
    FrameByFrame animation_of_explosion;
    sf::Vector2f position;
    std::string sound_name;
    std::chrono::milliseconds explosion_delay;
    float scale;
    bool is_sound_played = false;
    
    Stopwatch<> stopwatch;
};


#endif // FUSEGAME_EXPLOSION_HPP
