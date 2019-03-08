// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 24.02.2019.
//

#include "../Utility/MemoryTextureStorage/MemoryTextureStorage.hpp"
#include "Enemy.hpp"
#include "../Animations/HitpointsDecrease/HitpointsDecrease.hpp"

Enemy::Enemy(
    MovementBorders borders_for_laser,
    Player& player,
    Enemies const& enemies,
    sf::Vector2f position,
    sf::Vector2f speed,
    Timer<> move_timer,
    float speed_increase,
    Timer<> speed_up_timer,
    float hitpoints
)
: borders_for_laser(borders_for_laser)
, angry_smile(angry_smile_image.sprite)
, circular_thorns (
    sf::Sprite(crown_of_thorns_image.sprite),
    random() % 2 ? Rotation::Direction::Anticlockwise : Rotation::Direction::Clockwise,
    1, 1ms
  )
, player          (player)
, enemies         (enemies)
, circle          (getRadius(), position)
, speed           (speed)
, move_timer      (move_timer)
, speed_increase  (speed_increase)
, speed_up_timer  (speed_up_timer)
, hitpoints(hitpoints)
{ }

bool Enemy::operator< (Enemy const& other) const {
    return
        length(player.getGeometry().position - this->circle.position) <
        length(player.getGeometry().position - other.circle.position);
}
Circle Enemy::getGeometry() const {
    return circle;
}


ProgramEvents Enemy::update() {
    ProgramEvents generated_events;
    
    circular_thorns.changeDegree(1000.0f / distanceToPlayer());
    circular_thorns.update();
    move();
    speed_update();
    
    if(hitpoints <= 0) {
        append(generated_events, handleDeath());
        return generated_events;
    }
    
    if(circular_damage_delay.resetCheckIntervalExpired()) {
        float damage = calcDamageForPlayer();
        if(damage > 0) {
            generated_events.push_back(PlayerTookDamage { damage });
        }
    }
    
    if(shoot_delay.resetCheckIntervalExpired() && borders_for_laser.isIn(circle.position)) {
        sf::Vector2f move_vector = normalize(
            player.getGeometry().position - circle.position
        );
        generated_events.push_back(SoundPlay { "EnemyShot" });
        generated_events.push_back(ConstructedObject {
            new FlyingSimpleBeam(
                circle.position + move_vector * circle.R * 1.1f, move_vector,
                specRandom(5, 10), borders_for_laser
            )
        });
    }
    
    append(generated_events, eventsWalker( RUN_FOR_ALL_OF_RECEIVED_EVENTS {
        if(std::holds_alternative<SimpleBeamMoved>(e)) {
            SimpleBeamMoved const& beam = std::get<SimpleBeamMoved>(e);
            append(generated_events, handleSimpleBeamMotion(beam));
        }
        
        if(std::holds_alternative<MassiveExplosion>(e)) {
            MassiveExplosion const& massive_explosion = std::get<MassiveExplosion>(e);
            append(generated_events, handleMassiveExplosion(massive_explosion));
        }
    }));
    
    if(hitpoints <= 0) {
        append(generated_events, handleDeath());
    }
    
    return generated_events;
}
void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(circle.position);
    target.draw(angry_smile, states);
    target.draw(circular_thorns, states);
}
void Enemy::notify(ProgramEvent e) {
    received_events.push_back(e);
}

float Enemy::calcDamageForPlayer() const {
    Circle::Intersection intersection_with_player = player.getGeometry().intersection(circle);
    float intersect_length = length(
        intersection_with_player.A - intersection_with_player.B
    );
    
    if(player.getGeometry().isInside(circle.position)) {
        return specRandom(10, 20);
    } else if(intersection_with_player.isExists()) {
        return intersect_length * damage_circular_multipler;
    } else {
        return 0;
    }
}

ProgramEvents Enemy::startDeath() {
    ProgramEvents generated_events;
    generated_events.push_back(EnemyDestroyedByPlayer());
    
    auto count_explosions = specRandom(0, 4);
    for(int i = 0; i != count_explosions; ++i) {
        generated_events.push_back(
            ConstructedObject {
                new Explosion(
                    random() % 4, randExplosionPosition(),
                    std::chrono::milliseconds(
                        specRandom(0ll, linear_death.deathTime() - 200ll)
                    )
                )
            }
        );
    }
    
    linear_death.startDie();
    
    return generated_events;
}
ProgramEvents Enemy::handleDeath() {
    ProgramEvents generated_events;
    
    if(!linear_death.isDying()) {
        append(generated_events, startDeath());
        return generated_events;
    }
    
    if(linear_death.continueDying(angry_smile)) {
        generated_events.push_back(DestructedObject { this });
    }
    
    return generated_events;
}


ProgramEvents Enemy::handleSimpleBeamMotion(SimpleBeamMoved const& beam) {
    ProgramEvents generated_events;
    
    if(circle.isInside(beam.new_position) && hitpoints > 0) {
        hitpoints -= beam.damage_excepted;
        generated_events.push_back(SimpleBeamHit { beam.beam_id });
    }
    
    return generated_events;
}
ProgramEvents Enemy::handleMassiveExplosion(MassiveExplosion const& massive_explosion) {
    ProgramEvents generated_events;
    
    float received_damage = massive_explosion(circle.position);
    if(received_damage > 0) {
        hitpoints -= received_damage;
        generated_events.push_back(ConstructedObject {
            massive_explosion.hitpointsDecreaseAnimation(received_damage, circle.position)
        });
    } else {
        return generated_events;
    }
    
    return generated_events;
}

void Enemy::speed_update() {
    float enemy_step_length = length(speed);
    float player_step_length = length(player.getSpeed());
    bool speed_limit_reach = enemy_step_length > player_step_length*2;
    if(!speed_up_timer.resetCheckIntervalExpired() || speed_limit_reach) {
        return;
    }
    
    speed = speed + normalize(speed)*speed_increase;
}
void Enemy::move() {
    if(!move_timer.resetCheckIntervalExpired()) {
        return;
    }
    
    Circle player_geometry = player.getGeometry();
    // Because enemy has a saw and must collide with player.
    player_geometry.R *= 0.75;
    
    // Expected new position of enemy for next step.
    Circle estimated_circle = getGeometry();
    
    
    // First of all, calculate new position nearer to player.
    auto calcMotionVector = [&] (sf::Vector2f direction) {
        direction = normalize(direction);
        direction.x *= speed.x;
        direction.y *= speed.y;
        return direction;
    };
    estimated_circle.position += calcMotionVector(
        player_geometry.position - estimated_circle.position
    );
    
    
    // Now checks collisions with other enemies
    // and correct estimated position considering with other enemies.
    for(Enemy::Ptr const& other_enemy: enemies) {
        if(other_enemy.get() == this) {
            continue;
        }
        Circle other_geometry = other_enemy->getGeometry();
        
        if(estimated_circle.intersection(other_geometry).isExists()) {
            // Correcting estimated enemy position
            // for avoid collision with other enemy.
            estimated_circle.position = this->circle.position + normalize(
                (this->circle.position - other_geometry.position)
            );
            
            // Move estimated position of enemy along with it motion vector.
            estimated_circle.position = this->circle.position + calcMotionVector(
                estimated_circle.position - this->circle.position
            );
        }
    }
    
    // Apply new position if there are no intersection with anyone.
    Circle::Intersection intersects_with_player = estimated_circle.intersection(player_geometry);
    bool is_apply_position = !intersects_with_player.isExists();
    for(Enemy::Ptr const& other_enemy: enemies) {
        if(other_enemy.get() == this) {
            continue;
        }
        if(is_apply_position) {
            is_apply_position = !estimated_circle.intersection(other_enemy->getGeometry()).isExists();
        } else {
            break;
        }
    }
    
    if(is_apply_position) {
        circle.position = estimated_circle.position;
    }
}
float Enemy::distanceToPlayer() const {
    return length(player.getGeometry().position - circle.position);
}

sf::Vector2f Enemy::randExplosionPosition() const {
    sf::Vector2f rand_unit_vector = randUnitVector();
    return circle.position + sf::Vector2f(
        rand_unit_vector.x * (circle.R * (specRandom(0, 100) / 100.0f)) / 2.0f,
        rand_unit_vector.y * (circle.R * (specRandom(0, 100) / 100.0f)) / 2.0f
    );
}


float Enemy::getRadius() {
    return std::max(
        crown_of_thorns_image.texture_size.x / 2.0f,
        crown_of_thorns_image.texture_size.y / 2.0f
    );
}


