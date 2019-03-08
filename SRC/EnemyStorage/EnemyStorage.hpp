//
// Created by Lyosha12 on 24.02.2019.
//

#ifndef FUSEGAME_ENEMYGENERATOR_HPP
#define FUSEGAME_ENEMYGENERATOR_HPP

#include <vector>
#include <random>
#include <chrono>
#include "../Utility/GameObject.hpp"
#include "../Enemy/Enemy.hpp"
#include "../Utility/Math/Math.hpp"

class EnemyStorage: public GameObject {
  public:
    EnemyStorage(sf::VideoMode screen, Player& player);
    
    ProgramEvents update() override;
    void notify(ProgramEvent e) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
  private:
    void spawnEnemies();
    bool findFreeSpawnPos(Circle enemy_circle,float& current_angle, float& total_angle);
    
    MovementBorders calcMovementBorders(sf::VideoMode screen) {
        return {
            { 0, 0 },
            { static_cast<float>(screen.width), static_cast<float>(screen.height) }
        };
    }
    size_t calcMaxEnemiesOnSpawnArea();
    size_t calcMaxEnemies(size_t player_frags) const;
    float calcSpawnArc();
    
    sf::Vector2f pointOnSpawnCircle(float angle);
    
    
  private:
    MovementBorders borders_for_enemy_laser;
    Enemy::Enemies enemies;
    Player& player;
    
    Circle spawn_area;
    // Curve of spawn area what circle of enemy are occupied, in degrees.
    float spawn_arc;
    size_t max_enemies, max_enemies_on_spawn_arc;
};


#endif //FUSEGAME_ENEMYGENERATOR_HPP
