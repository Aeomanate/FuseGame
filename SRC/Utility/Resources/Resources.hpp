//
// Created by Lyosha12 on 08.03.2019.
//

#ifndef FUSEGAME_SPRITESHEETS_HPP
#define FUSEGAME_SPRITESHEETS_HPP

#include "../MemoryTextureStorage/MemoryTextureStorage.hpp"

extern std::vector<char> const font_source;


extern MemoryTextureStorage simple_explosion_sheet1;
extern MemoryTextureStorage simple_explosion_sheet2;
extern MemoryTextureStorage simple_explosion_sheet3;
extern MemoryTextureStorage simple_explosion_sheet4;
extern MemoryTextureStorage const& getExplosionStorage (size_t index);

extern MemoryTextureStorage const crown_of_thorns_image;
extern MemoryTextureStorage const angry_smile_image;

extern MemoryTextureStorage const massive_beam_sprite_sheet;
extern MemoryTextureStorage const massive_explosion_sprite_sheet;

extern MemoryTextureStorage const simple_beam_sprite_sheet;

#endif // FUSEGAME_SPRITESHEETS_HPP
