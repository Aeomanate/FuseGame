// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 24.02.2019.
//

#include "../Animations/HitpointsDecrease/HitpointsDecrease.hpp"
#include "Player.hpp"

const MemoryTextureStorage Player::player_image {
    "Player64",
    { 64, 64 },
    { 0, -1 },
    [] (MemoryTextureStorage& texture_storage) {
        texture_storage.sprite.setOrigin({
            texture_storage.frame_size.x / 2.0f,
            texture_storage.frame_size.y / 2.0f
        });
    }
};

const MemoryTextureStorage Player::player_death_sprite_sheet {
    "PlayerDeathSpriteSheet",
    { 1800, 1200 },
    { 0, 0 },
    [] (MemoryTextureStorage& texture_storage) {
        texture_storage.sprite.setOrigin({
            texture_storage.frame_size.x / 2.0f,
            texture_storage.frame_size.y / 2.0f
        });
    },
    { 6, 4 }
};

Player::Player(sf::VideoMode const& screen)
: player_sprite(player_image.sprite)
, circle(getRadius(), { screen.width*0.5f, screen.height*0.5f })
, movement_borders(calcMovementBorders(screen))
, lasers_controller(circle, current_direction, movement_borders)
{ }



ProgramEvents Player::update() {
    ProgramEvents generated_events;
    
    if(isAlive()) {
        append(generated_events, eventsWalker( RUN_FOR_ALL_OF_RECEIVED_EVENTS {
            if(std::holds_alternative<InputState>(e)) {
                    // On each(!) game cycle.
                    InputState const& input = std::get<InputState>(e);
                    move(input);
                    append(generated_events, lasers_controller.update());
                }
            
            if(std::holds_alternative<SimpleBeamMoved>(e)) {
                SimpleBeamMoved const& simple_beam = std::get<SimpleBeamMoved>(e);
                
                if(circle.isInside(simple_beam.new_position)) {
                    // FIXME: Make Hitpoints controller
                    //  - for drawing hitpoints decreases.
                    hitpoints -= simple_beam.damage_excepted;
                    generated_events.push_back(SimpleBeamHit { simple_beam.beam_id });
                }
            }
                
            if(std::holds_alternative<PlayerTookDamage>(e)) {
                float damage = std::get<PlayerTookDamage>(e).value;
                hitpoints -= damage;
                generated_events.push_back(ConstructedObject {
                    new HitpointsDecrease(
                        damage, circle.position, sf::Color(255, 100, 255)
                    )
                });
            }
            
            if(std::holds_alternative<MassiveExplosion>(e)) {
                float damage = std::get<MassiveExplosion>(e).damage_calculator(circle.position);
                hitpoints -= damage;
                if(damage > 0 && !isAlive()) {
                    generated_events.push_back(PlayerKilledHimself());
                }
            }
        }));
        
        if(!isAlive()) {
            generated_events.push_back(SoundStop { "MassiveAccumulation" });
            generated_events.push_back(ConstructedObject {
                new Explosion (
                    FrameByFrame(massive_explosion_sprite_sheet, 60),
                    circle.position, "MassiveExplosion", 100ms, 1.0f
                )
            });
            generated_events.push_back(ConstructedObject {
                new Explosion (
                    FrameByFrame(massive_explosion_sprite_sheet, 60),
                    circle.position, "MassiveExplosion", 200ms, 3.0f
                )
            });
            generated_events.push_back(ConstructedObject {
                new Explosion (
                    FrameByFrame(massive_explosion_sprite_sheet, 60),
                    circle.position, "MassiveExplosion", 400ms, 5.0f
                )
            });
            generated_events.push_back(PlayerDestroyedByEnemy());
        }
        
    } else {
        append(generated_events, handleDeath());
    }
    
    return generated_events;
}
void Player::notify(ProgramEvent program_event) {
    received_events.push_back(program_event);
    lasers_controller.notify(program_event);
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(circle.position);
    states.transform.rotate(angle(current_direction, player_image.orientation));
    target.draw(player_sprite, states);
}

void Player::move(InputState const& input) {
    sf::Vector2f new_direction = normalize(input.mouse_position - circle.position);
    
    if(length(new_direction) > 1e-3) {
        current_direction = new_direction;
    }
    if(!move_delay.resetCheckIntervalExpired()) {
        return;
    }
    
    
    sf::Vector2f result_motion = { 0, 0 };
    
    // Forward and backward motion.
    if(int sign = input.W - input.S; sign) {
        result_motion.x += speed.x * current_direction.x * sign;
        result_motion.y += speed.y * current_direction.y * sign;
    }
    
    // Circle motion to left or to right, depends on current direction.
    if(int sign = input.D - input.A; sign) {
        sf::Vector2f rotate_direction = sf::Transform().rotate(sign*90)*current_direction;
        result_motion.x += speed.x * rotate_direction.x;
        result_motion.y += speed.y * rotate_direction.y;
    }
    
    circle.position.x += result_motion.x;
    circle.position.y += result_motion.y;
    
    circle.position.x = std::max(circle.position.x, movement_borders.min.x);
    circle.position.y = std::max(circle.position.y, movement_borders.min.y);
    
    circle.position.x = std::min(circle.position.x, movement_borders.max.x);
    circle.position.y = std::min(circle.position.y, movement_borders.max.y);
}

ProgramEvents Player::handleDeath() {
    ProgramEvents generated_events;
    
    if(!isAlive() && !linear_death.isDying()) {
        linear_death.startDie();
        generated_events.push_back(PlayerDestroyedByEnemy());
        generated_events.push_back(ConstructedObject {
           new Explosion(
               FrameByFrame(player_death_sprite_sheet, 60),
               circle.position,
               "PlayerDeathSound"
           )
        });
        generated_events.push_back(MusicPause());
    }
    
    if(linear_death.isDied()) {
        generated_events.push_back(DestructedObject { this });
    }
    
    linear_death.continueDying(player_sprite);
    
    return generated_events;
}


std::chrono::milliseconds Player::getMoveDelay() const {
    return move_delay.getInterval<std::chrono::milliseconds>();
}
sf::Vector2f              Player::getSpeed() const {
    return speed;
}
Circle                    Player::getGeometry() const {
    return circle;
}
float                     Player::getRadius() {
    return std::max(
        player_image.texture_size.x / 2.0f,
        player_image.texture_size.y / 2.0f
    );
}
bool                      Player::isAlive() const {
    return hitpoints > 0;
}

MovementBorders Player::calcMovementBorders(sf::VideoMode const& screen) {
    std::vector<float> distances = {
        player_image.sprite.getOrigin().x,
        player_image.sprite.getOrigin().y,
        std::abs(player_image.texture_size.x - player_image.sprite.getOrigin().x),
        std::abs(player_image.texture_size.y - player_image.sprite.getOrigin().y)
    };
    float radius = *std::max_element(distances.begin(), distances.end());
    
    sf::Vector2f p1 = { radius, radius };
    sf::Vector2f p2 = { screen.width - radius, screen.height - radius };
    return { p1, p2 };
}

