//
// Created by Lyosha12 on 02.03.2019.
//

#ifndef FUSEGAME_MASSIVELASER_HPP
#define FUSEGAME_MASSIVELASER_HPP

#include "../../Utility/GameObject.hpp"
#include "../../Utility/ProgramEvents/ProgramEvents.hpp"
#include "../../Utility/Math/Math.hpp"
#include "../../Utility/Time/Timer.hpp"
#include "../../Animations/FrameByFrame/FrameByFrame.hpp"
#include "../MassiveLaser/GenerateBeam.hpp"
#include "../SimpleLaser/FlyingSimpleBeam.hpp"

struct MassiveLaserParams {
    float fatal_radius = 100;
    float max_radius = 500;
    float max_damage = 300;
    float max_distance = 600;
    
    struct AccumulationLimits {
        std::chrono::milliseconds min, max;
    } accumulation_limits { 4900ms, 11500ms };
    
    struct SpeedLimits {
        sf::Vector2f min, max;
    } speed_limits { { 10, 10 }, { 18, 18 } };
    
    
    struct SpeedLaw {
        struct AccumulationInterval {
            uintmax_t min, max;
        };
        SpeedLaw(AccumulationLimits time, SpeedLimits speed)
        : x_law ({ float(time.min.count()), speed.max.x }, { float(time.max.count()), speed.min.x })
        , y_law ({ float(time.min.count()), speed.max.y }, { float(time.max.count()), speed.min.y })
        { }
        
        sf::Vector2f getSpeed(std::chrono::milliseconds passed_ms) const {
            return {
                x_law.ordinate(float(passed_ms.count())),
                y_law.ordinate(float(passed_ms.count()))
            };
        }
        
      private:
        Line x_law,  y_law;
    } speed_law { accumulation_limits, speed_limits };
    
    inline float explosionScale(float cur_radius) const {
        return cur_radius*1.5f / max_radius;
    }
    
    Stopwatch<> stopwatch;
    Timer<> cooling = 20s;
};

// Laser as object what can generate a laser beam. Controlled by player.
class LasersController: public GameObject {
  public:
    LasersController(
        Circle const& player_circle,
        sf::Vector2f const& player_direction,
        MovementBorders movement_borders
    );
  
  public:
    ProgramEvents update() override;
    void notify(ProgramEvent e) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
    
    ProgramEvents handleInput(InputState const& input);
    
  private:
    ProgramEvents handleMassiveLaser(InputState const& input);
    ProgramEvents handleSimpleLaser(InputState const& input);
    
    sf::Vector2f calcTargetPoint() const;
    sf::Vector2f calcMassiveBeamSpeed() const;
    
    // Take the equation of line through two points:
    // (x - x1) / (x2 - x1) = (y - y1) / (y2 - y1).
    // \D is the damage value for
    // @R, where @R is radius relative to the center of explosion.
    //
    // @D1 - is max damage, @D1 = @max_damage,
    // @D2 - is min damage, @D2 = 0.
    // @R1 - is bound of circle, where on bound of @R1 damage is @D1.
    // The closer to the center of the explosion, the higher the damage.
    // @R2 - is max coverage radius where on bound damage is @D2.
    // In this case function for calc the damage on selected point (R, D) is
    // D = D1 + (R - R1) * (D2 - D1) / (R2 - R1) or if simplify
    // D = max_damage * (1 + R1 - R) / (R2 - R1).
    float R1() const;
    float R2() const;
    MassiveExplosion::DamageCalculator createDamageCalculator(sf::Vector2f explosion_center) const;
    
  private:
    Circle const& player_circle;
    sf::Vector2f const& player_direction;
    MassiveLaserParams massive_laser;
    
    Timer<> simple_laser_timeout = 600ms;
    MovementBorders movement_borders;
};


#endif //FUSEGAME_MASSIVELASER_HPP
