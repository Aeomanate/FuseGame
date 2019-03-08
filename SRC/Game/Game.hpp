//
// Created by Lyosha12 on 01.03.2019.
//

#ifndef FUSEGAME_GAME_HPP
#define FUSEGAME_GAME_HPP

#include <vector>
#include <memory>
#include <SFML/Window/VideoMode.hpp>
#include "../Animations/FrameByFrame/FrameByFrame.hpp"
#include "../Utility/MemoryTextureStorage/MemoryTextureStorage.hpp"
#include "../Utility/ProgramEvents/ProgramEvents.hpp"
#include "../Utility/GameObject.hpp"

class Game {
  public:
    Game(sf::VideoMode screen = calcOptimalRectangle());
    void run();
    
  private:
    static sf::VideoMode calcOptimalRectangle();
    
    void handleEvents();
    void updateObjects();
    void drawObjects();
    InputState getPressedKeys();
    
  private:
    const MemoryTextureStorage background;
    sf::RenderWindow window;
    std::vector<std::unique_ptr<GameObject>> objects;
    bool is_game_work = true;
    
    bool is_march_8_mode = false;
};


#endif //FUSEGAME_GAME_HPP
