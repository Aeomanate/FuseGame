// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 08.03.2019.
//

#include "Resources.hpp"

static const auto sprite_start_settings = [] (MemoryTextureStorage& texture_storage) {
    sf::Sprite& sprite = texture_storage.sprite;
    sf::Vector2u const& frame_size = texture_storage.frame_size;
    sprite.setOrigin({ frame_size.x / 2.0f, frame_size.y / 2.0f });
};

std::vector<char> const font_source {
    loadFromFileRawData("BlizzardDOTRusbyme")
};

MemoryTextureStorage simple_explosion_sheet1 {
    "SimpleExplosionSpriteSheet1",
    { 930,  465 },  { 0, 0 }, sprite_start_settings, { 6,  3 }
};
MemoryTextureStorage simple_explosion_sheet2 {
    "SimpleExplosionSpriteSheet2",
    { 465,  1860 }, { 0, 0 }, sprite_start_settings, { 3,  12 }
};
MemoryTextureStorage simple_explosion_sheet3 {
    "SimpleExplosionSpriteSheet3",
    { 465,  1860 }, { 0, 0 }, sprite_start_settings, { 3,  12 }
};
MemoryTextureStorage simple_explosion_sheet4 {
    "SimpleExplosionSpriteSheet4",
    { 2015, 310 },  { 0, 0 }, sprite_start_settings, { 13, 2 }
};

MemoryTextureStorage const& getExplosionStorage (size_t index) {
    switch(index) {
        case 0:
            return simple_explosion_sheet1;
            break;
        case 1:
            return simple_explosion_sheet2;
            break;
        
        case 2:
            return simple_explosion_sheet3;
            break;
        
        case 3:
            return simple_explosion_sheet4;
            break;
        
        default:
            throw std::logic_error(
                "Try to take explosion index #" + std::to_string(index) + ", " +
                "Max explosions index: " + std::to_string(3)
            );
    }
}



const MemoryTextureStorage crown_of_thorns_image {
    "CrownOfThorns",
    { 64, 64 },
    { 0, 0 },
    [] (MemoryTextureStorage& texture_storage) {
        texture_storage.sprite.setOrigin({
            texture_storage.frame_size.x / 2.0f,
            texture_storage.frame_size.y / 2.0f
        });
    }
};
const MemoryTextureStorage angry_smile_image {
    "AngrySmile",
    { 64, 64 },
    { 0, 0 },
    [] (MemoryTextureStorage& texture_storage) {
        texture_storage.sprite.setOrigin({
            texture_storage.frame_size.x / 2.0f,
            texture_storage.frame_size.y / 2.0f
        });
    }
};

MemoryTextureStorage const  massive_beam_sprite_sheet {
    "MassiveBeamSpriteSheet",
    { 228, 1330 },
    { -1, 0 },
    MemoryTextureStorage::dontTouchAnything,
    { 2, 19 }
};
MemoryTextureStorage const  massive_explosion_sprite_sheet {
    "MassiveExplosionSpriteSheet",
    { 8400, 8400 },
    { 0, 0 },
    MemoryTextureStorage::dontTouchAnything,
    { 14, 14 }
};

MemoryTextureStorage const  simple_beam_sprite_sheet {
    "SimpleBeamSpriteSheet",
    { 400, 40 },
    { -1, 0 },
    [](MemoryTextureStorage& texture_storage) {
        texture_storage.sprite.setScale(1.5, 1.5);
    },
    { 8, 1 }
};