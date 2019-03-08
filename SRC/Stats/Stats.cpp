// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 02.03.2019.
//

#include "Stats.hpp"
#include "../Utility/IndexDataFile/IndexDataFile.hpp"

Stats::Stats() {
    if(!font.loadFromMemory(font_source.data(), font_source.size())) {
        throw std::invalid_argument("Font Stats was't found");
    }
    
    default_score_text.setFont(font);
    
    default_score_text.setCharacterSize(34);
    default_score_text.setFillColor(sf::Color(255, 200, 0)); // Orange.
    default_score_text.setOutlineColor(sf::Color(150, 51, 51)); // Brown.
    default_score_text.setOutlineThickness(4);
    default_score_text.setStyle(sf::Text::Bold);
    
    data.player_lifetime.start();
}


ProgramEvents Stats::update() {
    return eventsWalker( RUN_FOR_ALL_OF_RECEIVED_EVENTS {
        if(std::holds_alternative<EnemyDestroyedByPlayer>(e)) {
            ++data.enemies_killed;
            generated_events.push_back(StatsUpdated { data });
        }
        
        if(std::holds_alternative<PlayerDestroyedByEnemy>(e)) {
            data.player_lifetime.stop();
            generated_events.push_back(StatsUpdated { data });
        }
        
        // FIXME: Dirty
        if(data.enemies_killed >= 12 && data.enemies_killed != 777'777 && !data.player_lifetime.isEnable()) {
            using Clock = std::chrono::system_clock;
            std::time_t this_moment = Clock::to_time_t(Clock::now()); //-V795
            struct tm* parts = std::localtime(&this_moment);
            
            if(parts->tm_mday == 8 && parts->tm_mon + 1 == 3) {
                generated_events.push_back(Martch8Start());
                data.enemies_killed = 777'777;
            }
        }
    });
}
void Stats::notify(ProgramEvent e) {
    received_events.push_back(e);
}
void Stats::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Text score(default_score_text);
    score.setString(L"Очки: " + std::to_wstring(data.enemies_killed));
    
    sf::Text lifetime(default_score_text);
    lifetime.setString(L"Время жизни: " + data.player_lifetime.getText<
        std::chrono::hours,
        std::chrono::minutes,
        std::chrono::seconds
    >());
    
    lifetime.move({10, 0});
    score.move({10, 45});
    
    target.draw(lifetime, states);
    target.draw(score, states);
}