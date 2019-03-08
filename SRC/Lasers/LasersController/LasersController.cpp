// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 02.03.2019.
//

#include "LasersController.hpp"





LasersController::LasersController(
    Circle const& player_circle,
    sf::Vector2f const& player_direction,
    MovementBorders movement_borders
)
: player_circle(player_circle)
, player_direction(player_direction)
, movement_borders(movement_borders)
{ }

ProgramEvents LasersController::update() {
    return eventsWalker( RUN_FOR_ALL_OF_RECEIVED_EVENTS {
        if(std::holds_alternative<InputState>(e)) {
            InputState const& input = std::get<InputState>(e);
            append(generated_events, handleInput(input));
        }
    });
}
void LasersController::notify(ProgramEvent e) {
    received_events.push_back(e);
}
void LasersController::draw(sf::RenderTarget&, sf::RenderStates) const { }

ProgramEvents LasersController::handleInput(InputState const& input) {
    ProgramEvents generated_events;

    append(generated_events, handleMassiveLaser(input));
    append(generated_events, handleSimpleLaser(input));
    
    return generated_events;
}

ProgramEvents LasersController::handleMassiveLaser(InputState const& input) {
    ProgramEvents generated_events;
    
    // Start laser charging.
    if(!input.LMB && input.RMB) {
        if(massive_laser.cooling.checkIntervalExpired()) {
            // If not charging then begin charge.
            if(!massive_laser.stopwatch.isEnable()) {
                generated_events.push_back(SoundPlay { "MassiveAccumulation" });
                massive_laser.stopwatch.start();
            }
        } else {
            generated_events.push_back(SoundPlay { "MassiveCancelAccumulation" });
            return generated_events;
        }
        
    }

    // Stop laser charging and maybe shoot.
    auto passed_ms = massive_laser.stopwatch.getInterval<std::chrono::milliseconds>();
    
    bool is_charged = passed_ms >= massive_laser.accumulation_limits.max;
    bool shoot_is_alloved = passed_ms >= massive_laser.accumulation_limits.min;
    if(massive_laser.stopwatch.isEnable() && (!input.RMB || is_charged)) {
        massive_laser.stopwatch.stop();
        generated_events.push_back(SoundStop { "MassiveAccumulation" });
    
        if(!shoot_is_alloved) {
            // Cancel shooting.
            generated_events.push_back(SoundPlay { "MassiveCancelAccumulation" });
        } else {
            // Shoot-time!
            generated_events.push_back(SoundStop { "MassiveCancelAccumulation" });
            generated_events.push_back(SoundPlay { "MassiveShot" });
            massive_laser.cooling.reset();
        
            /*
            generated_events.push_back(ConstructedObject {
                new GenerateBeam (
                    player_circle,
                    player_direction
                )
            });
           
            */
            generated_events.push_back(ConstructedObject {
                new FlyingMassiveBeam (
                    player_circle.position + player_direction * 2.0f*player_circle.R,
                    player_direction,
                    calcTargetPoint(),
                    calcMassiveBeamSpeed(),
                    massive_laser.explosionScale(R2()),
                    createDamageCalculator(calcTargetPoint()),
                    movement_borders
                )
            });
        }
    }
    
    return generated_events;
}
ProgramEvents LasersController::handleSimpleLaser(InputState const& input) {
    ProgramEvents generated_events;
    
    if(input.LMB && !input.RMB) {
        if(!simple_laser_timeout.resetCheckIntervalExpired()) {
            return generated_events;
        }

        generated_events.push_back(SoundPlay { "PlayerShot" });
        generated_events.push_back(ConstructedObject {
            new FlyingSimpleBeam(
                player_circle.position + player_direction * player_circle.R * 0.75f,
                player_direction,
                specRandom(15, 35),
                movement_borders
            )
        });
    }
    
    return generated_events;
}

sf::Vector2f LasersController::calcTargetPoint() const {
    auto ms = massive_laser.stopwatch.getCount<std::chrono::milliseconds, size_t>();
    float shot_length = ms * massive_laser.max_distance / massive_laser.accumulation_limits.max.count();
    return player_circle.position + player_direction * shot_length;
}
sf::Vector2f LasersController::calcMassiveBeamSpeed() const {
    auto ms_passed = massive_laser.stopwatch.getInterval<std::chrono::milliseconds>();
    return massive_laser.speed_law.getSpeed(ms_passed);
}

float LasersController::R1() const  {
    auto ms = massive_laser.stopwatch.getCount<std::chrono::milliseconds, size_t>();
    return ms * massive_laser.fatal_radius / massive_laser.accumulation_limits.min.count();
}
float LasersController::R2() const {
    auto ms = massive_laser.stopwatch.getCount<std::chrono::milliseconds, size_t>();
    return ms * massive_laser.max_radius / massive_laser.accumulation_limits.max.count();
}


MassiveExplosion::DamageCalculator LasersController::createDamageCalculator(
    sf::Vector2f explosion_center
 ) const {
    float R1 = this->R1();
    float R2 = this->R2();
    // this->max_damage cannot be implicitly captured.
    float max_explosion_damage = massive_laser.max_damage;
    
    return
    [max_explosion_damage, R1, R2, explosion_center] (sf::Vector2f some_position) {
        float R = length(some_position - explosion_center);
        
        if(R >= R2) return 0.0f;
        return max_explosion_damage * (1 + R1 - R) / (R2 - R1);
    };
}
