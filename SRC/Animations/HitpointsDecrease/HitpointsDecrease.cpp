// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 07.03.2019.
//

#include "HitpointsDecrease.hpp"

HitpointsDecrease::HitpointsDecrease(float value, sf::Vector2f position, sf::Color color)
: start_position(position)
, cur_position(position)
, direction({ -1, 0 })
{
    if(!font.loadFromMemory(font_source.data(), font_source.size())) {
        throw std::invalid_argument("Font for HitpointsDecrease was't found");
    }
    
    text.setFont(font);
    
    text.setCharacterSize(24);
    text.setFillColor(color);
    text.setOutlineColor(sf::Color(150, 51, 51)); // Brown.
    text.setOutlineThickness(2);
    text.setStyle(sf::Text::Bold);
    
    std::ostringstream cutter;
    cutter.precision(2);
    cutter << std::fixed << '-' << value;
    
    text.setString(cutter.str());
    
    end_position = position + direction.x * sf::Vector2f { 120, -12 };
    sf::Vector2f parabola_peak = position + sf::Vector2f {
        length(end_position - position) / 2.0f,
        position.y + -6
    };
    
    text_trajectory = Parabola(
        position.x, position.y,
        parabola_peak.x, parabola_peak.y,
        end_position.x, end_position.y
    );
}

ProgramEvents HitpointsDecrease::update() {
    ProgramEvents generated_events;
    updateTextPosition();
    
    if(length(cur_position - end_position) < 1) {
        generated_events.push_back(DestructedObject { this });
        return generated_events;
    }
    
    return generated_events;
}
void HitpointsDecrease::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(cur_position);
    target.draw(text, states);
}
void HitpointsDecrease::notify(ProgramEvent e) {
    received_events.push_back(e);
}


void HitpointsDecrease::updateTextPosition() {
    if(!move_timer.resetCheckIntervalExpired()) {
        return;
    }
    
    float next_x = cur_position.x + direction.x * 2.0f;
    
    float next_y = text_trajectory.ordinate(next_x);
    cur_position = { next_x, next_y };
}
