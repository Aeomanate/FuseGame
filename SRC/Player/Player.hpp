//
// Created by Lyosha12 on 24.02.2019.
//

#ifndef FUSEGAME_PLAYER_HPP
#define FUSEGAME_PLAYER_HPP

#include <vector>
#include <algorithm>

#include "../Utility/MemoryTextureStorage/MemoryTextureStorage.hpp"
#include "../Utility/GameObject.hpp"
#include "../Utility/Observer.hpp"
#include "../Utility/Math/Math.hpp"
#include "../Utility/Resources/Resources.hpp"
#include "../Stats/Stats.hpp"
#include "../Animations/LinearDeath/LinearDeath.hpp"
#include "../Lasers/LasersController/LasersController.hpp"
#include "../Utility/MovementBorders.hpp"

class Player: public GameObject {
  public:
    
    Player(sf::VideoMode const& screen);
    
    std::chrono::milliseconds getMoveDelay() const;
    sf::Vector2f getSpeed() const;
    Circle getGeometry() const;
    bool isAlive() const;
  
  private:
    ProgramEvents update() override;
    void notify(ProgramEvent program_event) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
  private:
    void move(InputState const& input);
    ProgramEvents handleDeath();
    
  private:
    float getRadius();
    static MovementBorders calcMovementBorders(sf::VideoMode const& screen);
    
  private:
    static const MemoryTextureStorage player_image;
    static const MemoryTextureStorage player_death_sprite_sheet;
    sf::Sprite player_sprite;
    Circle circle;
    sf::Vector2f current_direction;
    
    MovementBorders movement_borders;
    sf::Vector2f speed = { 1.5, 1.5 };
    Timer<> move_delay = 15ms;
    
    LasersController lasers_controller;
    
    float hitpoints = 100;
    
    LinearDeath linear_death = 500ms;
};



#endif //FUSEGAME_PLAYER_HPP
