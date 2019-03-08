// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 06.03.2019.
//

#include <array>
#include "Explosion.hpp"

Explosion::Explosion(
    FrameByFrame explosion,
    sf::Vector2f position,
    std::string sound_name,
    std::chrono::milliseconds explosion_delay,
    float scale
)
: animation_of_explosion(explosion)
, position(position)
, sound_name(sound_name)
, explosion_delay(explosion_delay)
, scale(scale)
{ stopwatch.start(); }

Explosion::Explosion(
    size_t explosion_number,
    sf::Vector2f position,
    std::chrono::milliseconds explosion_delay
)
: Explosion(
    FrameByFrame(getExplosionStorage(explosion_number), 60),
    position,
    "Bomb" + std::to_string(1 + random() % 4),
    explosion_delay
  )
{ stopwatch.start(); }

ProgramEvents Explosion::update() {
    ProgramEvents generated_events;
    
    if(stopwatch.getInterval<std::chrono::milliseconds>() < explosion_delay) {
        return generated_events;
    }
    
    if(!is_sound_played) {
        generated_events.push_back(SoundPlay { sound_name });
        is_sound_played = true;
    }
    
    animation_of_explosion.update();
    
    if(animation_of_explosion.isAnimationStopped()) {
        generated_events.push_back(DestructedObject { this });
        return generated_events;
    }
    
    
    return generated_events;
}
void Explosion::notify(ProgramEvent) {
    // Empty.
}
void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(stopwatch.getInterval<std::chrono::milliseconds>() < explosion_delay) {
        return;
    }
    
    states.transform.translate(position);
    states.transform.scale({ scale, scale });
    target.draw(animation_of_explosion, states);
}
