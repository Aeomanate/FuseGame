// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 05.03.2019.
//

#include "MemoryTextureStorage.hpp"

MemoryTextureStorage::MemoryTextureStorage(
    std::string texture_name,
    sf::Vector2u texture_size,
    sf::Vector2f orientation,
    std::function<void(MemoryTextureStorage&)> sprite_settings,
    sf::Vector2u count_frames
)
: texture_size(texture_size)
, orientation(orientation)
, count_frames(count_frames)
, frame_size({ texture_size.x / count_frames.x, texture_size.y / count_frames.y })
{
    std::vector<char> raw = loadFromFileRawData(texture_name);
    
    if(!texture.create(texture_size.x, texture_size.y)) {
        throw std::runtime_error("Out of memory while load " + texture_name + ".");
    }
    
    if(!texture.loadFromMemory(raw.data(), raw.size())) {
        throw std::invalid_argument("Texture '" + texture_name + "' not loaded.");
    }
    
    texture.setSmooth(true);

    sprite.setTexture(texture);
    sprite_settings(*this);
}

ProgramEvents MemoryTextureStorage::update() { return { }; }
void MemoryTextureStorage::notify(ProgramEvent) { }
void MemoryTextureStorage::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}