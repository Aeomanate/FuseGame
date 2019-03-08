// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 08.03.2019.
//

#include "ProgramEvents.hpp"
#include "../../Animations/HitpointsDecrease/HitpointsDecrease.hpp"



float MassiveExplosion::operator() (sf::Vector2f position) const {
    return damage_calculator(position);
}
HitpointsDecrease* MassiveExplosion::hitpointsDecreaseAnimation(float damage, sf::Vector2f position) const {
    return new HitpointsDecrease(damage, position, sf::Color(255,165,0));
}