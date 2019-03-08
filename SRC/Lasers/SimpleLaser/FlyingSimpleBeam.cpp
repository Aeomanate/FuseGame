// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 06.03.2019.
//

#include "FlyingSimpleBeam.hpp"
#include "../../Animations/HitpointsDecrease/HitpointsDecrease.hpp"


FlyingSimpleBeam::FlyingSimpleBeam(
    sf::Vector2f position,
    sf::Vector2f direction,
    float damage,
    MovementBorders movement_borders
)
: simple_beam_animation(simple_beam_sprite_sheet, 45, -1)
, position(position)
, direction(direction)
, damage(damage)
, movement_borders(movement_borders)
{ }


ProgramEvents FlyingSimpleBeam::update() {
    ProgramEvents generated_events;
    
    simple_beam_animation.update();
    
    if(!move_fly_interval.resetCheckIntervalExpired()) {
        return generated_events;
    }
    
    position.x += direction.x * speed.x;
    position.y += direction.y * speed.y;
    
    generated_events.push_back(SimpleBeamMoved {
        position, damage, this->object_id
    });
    
    bool ist_hit = false;
    append(generated_events, eventsWalker( RUN_FOR_ALL_OF_RECEIVED_EVENTS {
        if(std::holds_alternative<SimpleBeamHit>(e)) {
            SimpleBeamHit const& hit_info = std::get<SimpleBeamHit>(e);
            
            if(hit_info.beam_id == this->object_id) {
                append(generated_events, handleHit(object_id));
                ist_hit = true;
            }
        }
    }));
    
    
    if(!ist_hit && !movement_borders.isIn(position)) {
        generated_events.push_back(ConstructedObject{
            new Explosion(random()%4, position)
        });
    
        generated_events.push_back(DestructedObject { this });
    }
    
    return generated_events;
}
void FlyingSimpleBeam::notify(ProgramEvent e) {
    received_events.push_back(e);
}
void FlyingSimpleBeam::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.rotate(
        angle(direction, simple_beam_sprite_sheet.orientation),
        position
    );
    states.transform.translate(position);
    
    
    target.draw(simple_beam_animation, states);
}


ProgramEvents FlyingSimpleBeam::handleHit(size_t beam_id) {
    ProgramEvents generated_events;
    
    if(beam_id != this->object_id) {
        return generated_events;
    }
    
    sf::Vector2f random_pos {
        static_cast<float>(random()%32),
        static_cast<float>(random()%32)
    };
    
    generated_events.push_back(DestructedObject { this });
    generated_events.push_back(ConstructedObject {
        new Explosion(random() % 4, position + random_pos)
    });
    generated_events.push_back(ConstructedObject {
        new HitpointsDecrease(damage, position + random_pos, sf::Color(255, 50, 50))
    });
    
    return generated_events;
}