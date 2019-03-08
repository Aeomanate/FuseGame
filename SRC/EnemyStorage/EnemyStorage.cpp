// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 24.02.2019.
//

#include "EnemyStorage.hpp"


EnemyStorage::EnemyStorage(
    sf::VideoMode screen,
    Player& player
)
: borders_for_enemy_laser(calcMovementBorders(screen))
, player(player)
, spawn_area(
      static_cast<float>(
          sqrt(
              std::pow(screen.width, 2) +
              std::pow(screen.height, 2)
          ) / 2 + Enemy::getRadius() + 1
      ),
      sf::Vector2f { screen.width / 2.0f, screen.height / 2.0f }
  )
, spawn_arc(calcSpawnArc())
, max_enemies(calcMaxEnemies(0))
, max_enemies_on_spawn_arc(calcMaxEnemiesOnSpawnArea())
{ }

ProgramEvents EnemyStorage::update() {
    ProgramEvents generated_events;
    
    bool is_player_destroyed = false;
    
    append(generated_events, eventsWalker( RUN_FOR_ALL_OF_RECEIVED_EVENTS {
        if(std::holds_alternative<StatsUpdated>(e)) {
            size_t count_frags = std::get<StatsUpdated>(e).data.enemies_killed;
            max_enemies = calcMaxEnemies(count_frags);
        }
        
        if(std::holds_alternative<PlayerDestroyedByEnemy>(e)) {
            is_player_destroyed = true;
            generated_events.push_back(DestructedObject { this });
        }
    }));
    
    if(is_player_destroyed) {
        return generated_events;
    }
    
    spawnEnemies();
    
    std::sort(
        enemies.begin(), enemies.end(),
        [] (Enemy::Ptr const& A, Enemy::Ptr const& B) {
            return *A < *B;
        }
    );
    
    
    for(auto& enemy: enemies) {
        append(generated_events, enemy->update());
    }
    
    
    
    
    auto event = generated_events.begin();
    while(event != generated_events.end()) {
        bool is_enemy_removed = false;
        if(std::holds_alternative<DestructedObject>(*event)) {
            for(auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy) {
                if(enemy->get() == std::get<DestructedObject>(*event).object) {
                    enemies.erase(enemy);
                    event = generated_events.erase(event);
                    is_enemy_removed = true;
                    break;
                }
            }
        }
        
        if(!is_enemy_removed) {
            ++event;
        }
    }
    
    
    return generated_events;
}
void EnemyStorage::notify(ProgramEvent e) {
    received_events.push_back(e);
    for(auto& enemy: enemies){
        enemy->notify(e);
    }
}
void EnemyStorage::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto const& enemy: enemies) {
        target.draw(*enemy, states);
    }
}

void EnemyStorage::spawnEnemies() {
    while(enemies.size() <= max_enemies && enemies.size() < max_enemies_on_spawn_arc) {
        float current_angle = specRandom(0, 360);
        float total_angle = 0;
        
        while(total_angle <= 360) {
            Circle enemy_circle(Enemy::getRadius(), pointOnSpawnCircle(current_angle));
            
            if(findFreeSpawnPos(enemy_circle, current_angle, total_angle)) {
                sf::Vector2f player_speed = player.getSpeed();
                std::chrono::milliseconds player_move_delay = player.getMoveDelay();
                
                Enemy* enemy;
                try {
                    enemy = new Enemy(
                        borders_for_enemy_laser,
                        player, enemies, enemy_circle.position,
                        player_speed*(0.5f + max_enemies/100.0f),
                        player_move_delay, length(player_speed*0.1f), 15s,
                        150 + max_enemies/10.0f
                    );
                } catch(std::bad_alloc const& e) {
                    throw std::runtime_error("Enemy are not created, no free memory");
                }
                enemies.emplace_back(enemy);
                break;
            }
        }
    }
}
bool EnemyStorage::findFreeSpawnPos(Circle enemy_circle,float& current_angle, float& total_angle) {
    for(auto const& other_enemy: enemies) {
        if(enemy_circle.intersection(other_enemy->getGeometry()).isExists()) {
            current_angle += spawn_arc;
            total_angle += spawn_arc;
            return false;
        }
    }
    
    return true;
}

size_t EnemyStorage::calcMaxEnemiesOnSpawnArea() {
    return static_cast<size_t>(360 / (2 * spawn_arc));
}
size_t EnemyStorage::calcMaxEnemies(size_t player_frags) const {
    return static_cast<size_t>(player_frags/4 + 1.5*log2(player_frags) + 1);
}
float EnemyStorage::calcSpawnArc() {
    Circle enemy_circle { Enemy::getRadius(), pointOnSpawnCircle(0)};
    Circle::Intersection circle_circle = spawn_area.intersection(enemy_circle);
    if(circle_circle.count != 2) {
        throw std::logic_error("Circle intersection are not work!");
    }
    
    sf::Vector2f X = circle_circle.A - spawn_area.position;
    sf::Vector2f Y = circle_circle.B - spawn_area.position;
    return static_cast<float>(acos(scalarProduction(X, Y) / (length(X) * length(Y))));
}

sf::Vector2f EnemyStorage::pointOnSpawnCircle(float angle) {
    return {
        spawn_area.position.x + spawn_area.R * std::cos(angle),
        spawn_area.position.y + spawn_area.R * std::sin(angle)
    };
}