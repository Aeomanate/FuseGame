// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 01.03.2019.
//

#include "../Utility/MemoryTextureStorage/MemoryTextureStorage.hpp"
#include "../../Resources/ImageSources/Icon/FuseGameIcon.hpp"
#include "../Player/Player.hpp"
#include "../EnemyStorage/EnemyStorage.hpp"
#include "../AudioPlayer/AudioPlayer.hpp"
#include "../Utility/WindowForTests/WindowForTests.hpp"
#include "../March8/March8.hpp"
#include "Game.hpp"

Game::Game(sf::VideoMode screen)
: background (
    "Background", { 800, 600 }, { 0, 0 },
    [&screen] (MemoryTextureStorage& texture_storage) {
        texture_storage.sprite.setScale(float(screen.width) / 800, float(screen.height) / 600.0f);
    },
    { 1, 1 }
  )
, window(screen, "Fuse Game", sf::Style::None)
{
    window.setIcon(FUSEGAME_ICON.width, FUSEGAME_ICON.height, FUSEGAME_ICON.pixel_data);
    window.setFramerateLimit(60);
    
    try {
        Stats* statistics = new Stats();
        Player* player = new Player(screen);
        EnemyStorage* enemy_storage = new EnemyStorage(screen, *player);
        AudioPlayer* audio_player = new AudioPlayer();
        
        objects.emplace_back(statistics);
        objects.emplace_back(player);
        objects.emplace_back(enemy_storage);
        objects.emplace_back(audio_player);
    } catch(std::bad_alloc const& e) {
        throw std::runtime_error("Not enough memory, game is not be able to run");
    }
}

void Game::run() {
    while(is_game_work) {
        if(!window.hasFocus()) {
            // continue;
        }
        handleEvents();
        updateObjects();
        drawObjects();
    }
}

sf::VideoMode Game::calcOptimalRectangle() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // auto min = std::min(desktop.width, desktop.height);
    return desktop;
}

void Game::handleEvents() {
    sf::Event e;
    while(window.pollEvent(e)) {
        switch(e.type) {
            case sf::Event::KeyPressed:
                if(e.key.code == sf::Keyboard::Escape) {
                    window.close();
                    is_game_work = false;
                }
                break;
                
            case sf::Event::Closed:
                window.close();
                is_game_work = false;
                break;
            
            
            default:
                break;
        }
    }
    
    for(auto& object: objects) {
        object->notify(ProgramEvent(getPressedKeys()));
    }
}
void Game::updateObjects() {
    ProgramEvents generated_events;
    
    for(auto& object: objects) {
        append(generated_events, object->update());
    }
    
    for(auto const& e: generated_events) {
        if(std::holds_alternative<Martch8Start>(e)) {
            is_march_8_mode = true;
            objects.insert(objects.begin()++, std::unique_ptr<GameObject> { new March8(window.getSize()) });
        }
        
        if(std::holds_alternative<PlayerDestroyedByEnemy>(e)) {
            // Set game-over mode for restart or exit
        }
    
        if(std::holds_alternative<DestructedObject>(e)) {
            GameObject* to_remove = std::get<DestructedObject>(e).object;
        
            auto object_iterator = objects.begin();
            while(object_iterator != objects.end()) {
                if((*object_iterator).get() == to_remove) {
                    objects.erase(object_iterator);
                    break;
                }
                ++object_iterator;
            }
        
            continue;
        }
        
        if(std::holds_alternative<ConstructedObject>(e)) {
            GameObject* to_add = std::get<ConstructedObject>(e).object;
            objects.push_back( std::unique_ptr<GameObject> { to_add } );
            continue;
        }
        
        for(auto& object: objects) {
            // * Object X that generates the Y event
            //   will receive this Y event back.
            //   It can be prevented by adding information to the X object
            //   about the types that this X object is waiting for to handle.
            // * Objects Z, witch obey object X, can receive event Y twice.
            // * So new events should be distributed only to top of hierarchy.
            object->notify(e);
        }
    }
}
void Game::drawObjects() {
    window.clear();
    
    window.draw(background);
    for(auto const& object: objects) {
        window.draw(*object);
    }
    
    window.display();
}

InputState Game::getPressedKeys() {
    InputState input_state;
    input_state.W   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    input_state.S   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    input_state.A   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    input_state.D   = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    input_state.LMB = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    input_state.RMB = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
    
    sf::Vector2i cursor = sf::Mouse::getPosition(window);
    input_state.mouse_position = {
        static_cast<float>(cursor.x),
        static_cast<float>(cursor.y)
    };
    
    return input_state;
}