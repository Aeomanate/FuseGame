// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 03.03.2019.
//

#include "FlyingMassiveBeam.hpp"


FlyingMassiveBeam::FlyingMassiveBeam(
    sf::Vector2f position,
    sf::Vector2f direction,
    sf::Vector2f target_position,
    sf::Vector2f speed,
    float massive_explosion_scale,
    MassiveExplosion::DamageCalculator damage_calculator,
    MovementBorders movement_borders
)
: massive_beam_animation(massive_beam_sprite_sheet, 24, -1)
, position(position)
, direction(direction)
, target_position(target_position)
, speed(speed)
, massive_explosion_scale(massive_explosion_scale)
, damage_calculator(damage_calculator)
, movement_borders(movement_borders)
{ }

ProgramEvents FlyingMassiveBeam::update() {
    ProgramEvents generated_events;
    
    massive_beam_animation.update();
    
    if(!move_fly_interval.resetCheckIntervalExpired()) {
        return generated_events;
    }
    
    bool is_target_reached = length(position - target_position) < massive_beam_sprite_sheet.frame_size.x/2.0f;
    bool is_in_screen = movement_borders.isIn(position);
    if(is_target_reached || !is_in_screen) {
        generated_events.push_back(DestructedObject { this });
        generated_events.push_back(ConstructedObject {
            new Explosion(
                FrameByFrame { massive_explosion_sprite_sheet, 60 },
                target_position,
                "MassiveExplosion",
                0ms,
                massive_explosion_scale
            )
        });
        generated_events.push_back(MassiveExplosion { damage_calculator });
    }
    
    position.x += direction.x * speed.x;
    position.y += direction.y * speed.y;
    
    return generated_events;
}
void FlyingMassiveBeam::notify(ProgramEvent) { }
void FlyingMassiveBeam::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.rotate(
        angle(direction, massive_beam_sprite_sheet.orientation),
        position
    );
    states.transform.translate(position);
    
    target.draw(massive_beam_animation, states);
}