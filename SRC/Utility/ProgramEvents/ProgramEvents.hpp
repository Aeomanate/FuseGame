//
// Created by Lyosha12 on 24.02.2019.
//

#ifndef FUSEGAME_GAMEEVENT_HPP
#define FUSEGAME_GAMEEVENT_HPP

#include <vector>
#include <variant>
#include <functional>
#include <SFML/Window/Event.hpp>
#include "../../Stats/StatsData.hpp"

class HitpointsDecrease;

class GameObject;

struct InputState {
    bool W = false;
    bool S = false;
    bool A = false;
    bool D = false;
    bool LMB = false;
    bool RMB = false;
    sf::Vector2f mouse_position;
    
};

// This events are handled those what are responsible for array of GameObject*.
struct ConstructedObject { GameObject* object; };
struct DestructedObject { GameObject* object; };

struct PlayerKilledHimself { };
struct PlayerDestroyedByEnemy { };
struct EnemyDestroyedByPlayer { };
struct PlayerTookDamage  { float value; };
struct StatsUpdated      { StatsData data; };

struct MassiveExplosion {
    float operator() (sf::Vector2f position) const;
    HitpointsDecrease* hitpointsDecreaseAnimation(float damage, sf::Vector2f position) const;
    
    using DamageCalculator = std::function<float(sf::Vector2f)>;
    DamageCalculator damage_calculator;
};
struct SimpleBeamMoved {
    sf::Vector2f new_position;
    float damage_excepted;
    size_t beam_id;
};
struct SimpleBeamHit {
    size_t beam_id;
};

struct SoundPlay  { std::string sound_name; };
struct SoundStop  { std::string sound_name; };
struct MusicPlay  { };
struct MusicStop  { };
struct MusicPause { };

struct Martch8Start { };
struct Martch8End   { };
struct March8Music1End { };

using ProgramEvent =
    std::variant<
        InputState,
        ConstructedObject,
        DestructedObject,

        MassiveExplosion,
        SimpleBeamMoved,
        SimpleBeamHit,
        
        SoundPlay ,
        SoundStop ,
        MusicPlay ,
        MusicStop ,
        MusicPause,

        PlayerKilledHimself,
        PlayerDestroyedByEnemy,
        EnemyDestroyedByPlayer,
        PlayerTookDamage,
        StatsUpdated,
        
        Martch8Start,
        Martch8End,
        March8Music1End,
        sf::Event
    >;

using ProgramEvents = std::vector<ProgramEvent>;

inline void append(ProgramEvents& A, ProgramEvents&& B) {
    A.insert(A.end(), B.begin(), B.end());
}

#endif //FUSEGAME_GAMEEVENT_HPP
