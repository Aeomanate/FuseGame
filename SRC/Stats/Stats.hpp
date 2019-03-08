//
// Created by Lyosha12 on 02.03.2019.
//

#ifndef FUSEGAME_STATS_HPP
#define FUSEGAME_STATS_HPP



#include <chrono>
#include <SFML/Graphics/Text.hpp>
#include "../Utility/Time/Stopwatch.hpp"
#include "../Utility/ProgramEvents/ProgramEvents.hpp"
#include "../Utility/GameObject.hpp"
#include "../Utility/Resources/Resources.hpp"
#include "StatsData.hpp"

using namespace std::chrono_literals;


struct Stats: public GameObject {
  public:
    Stats();
    
    ProgramEvents update() override;
    void notify(ProgramEvent e) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
  private:
    StatsData data;
    sf::Font font;
    sf::Text default_score_text;
};



#endif //FUSEGAME_STATS_HPP
