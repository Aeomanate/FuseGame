//
// Created by Lyosha12 on 24.02.2019.
//

#ifndef FUSEGAME_ENEMY_HPP
#define FUSEGAME_ENEMY_HPP

#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include "../Animations/Rotation/Rotation.hpp"
#include "../Utility/GameObject.hpp"
#include "../Animations/LinearDeath/LinearDeath.hpp"
#include "../Player/Player.hpp"

class Enemy: public GameObject {
  public:
    using Ptr = std::unique_ptr<Enemy>;
    using Enemies = std::vector<Ptr>;
    
    Enemy(
        MovementBorders borders_for_laser,
        Player& player,
        Enemies const& enemies,
        sf::Vector2f position,
        sf::Vector2f speed,
        Timer<> move_timer,
        float speed_increase,
        Timer<> speed_up_timer,
        float hitpoints
    );
    
    bool operator< (Enemy const& other) const;
    
    Circle getGeometry() const;
    static float getRadius();
    
    ProgramEvents update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void notify(ProgramEvent e) override;
    
  private:
    float calcDamageForPlayer() const;
  
  private:
    ProgramEvents startDeath();
    ProgramEvents handleDeath();
    
    ProgramEvents handleSimpleBeamMotion(SimpleBeamMoved const& beam);
    ProgramEvents handleMassiveExplosion(MassiveExplosion const& massive_explosion);
    
  private:
    void move();
    void speed_update();
    float distanceToPlayer() const;
    
    sf::Vector2f randExplosionPosition() const;
    
  private:
    MovementBorders borders_for_laser;
    
    sf::Sprite angry_smile;
    Rotation circular_thorns;
    
    Player& player;
    Enemies const& enemies;
    
    Circle circle;
    sf::Vector2f speed;
    Timer<> move_timer;
    
    float speed_increase;
    Timer<> speed_up_timer;
    
    float hitpoints;
    LinearDeath linear_death = 500ms;
    
    float damage_circular_multipler = 0.2;
    Timer<> circular_damage_delay = 500ms;
    
    inline static Timer<> shoot_delay = 10s;
};


#endif //FUSEGAME_ENEMY_HPP
