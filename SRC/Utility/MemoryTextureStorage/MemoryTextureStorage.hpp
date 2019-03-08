//
// Created by Lyosha12 on 05.03.2019.
//

#ifndef FUSEGAME_MEMORYTEXTURESTORAGE_HPP
#define FUSEGAME_MEMORYTEXTURESTORAGE_HPP


#include <fstream>
#include <vector>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../GameObject.hpp"
#include "../IndexDataFile/IndexDataFile.hpp"

class MemoryTextureStorage: public GameObject {
  public:
    auto inline static const dontTouchAnything = [] (MemoryTextureStorage&) { };
    MemoryTextureStorage(
        std::string texture_name,
        sf::Vector2u texture_size,
        sf::Vector2f orientation = { 0, 0 },
        std::function<void(MemoryTextureStorage&)> sprite_settings = dontTouchAnything,
        sf::Vector2u count_frames = { 1, 1 }
    );
    MemoryTextureStorage(MemoryTextureStorage const&) = delete;
    
    ProgramEvents update() override;
    void notify(ProgramEvent) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
  public:
    sf::Vector2u const texture_size;
    sf::Vector2f const orientation;
    sf::Vector2u const count_frames;
    sf::Vector2u const frame_size;
    
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // FUSEGAME_MEMORYTEXTURESTORAGE_HPP
