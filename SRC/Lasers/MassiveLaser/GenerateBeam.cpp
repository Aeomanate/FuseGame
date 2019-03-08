// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 03.03.2019.
//

#include "GenerateBeam.hpp"

const MemoryTextureStorage GenerateBeam::massive_beam_generate_sprite_sheet {
    "MassiveBeamGenerateSpriteSheet",
    { 155, 5270 },
    { 1, 0 },
    [] (MemoryTextureStorage& texture_storage) {
        texture_storage.sprite.setOrigin(16, texture_storage.frame_size.y / 2.0f);
    },
    { 1, 34 }
};


GenerateBeam::GenerateBeam(
    Circle const& player_circle,
    sf::Vector2f const& player_direction
)
: massive_beam_generated(massive_beam_generate_sprite_sheet, 60)
, player_circle(player_circle)
, player_direction(player_direction)
{ }


ProgramEvents GenerateBeam::update() {
    massive_beam_generated.update();
    return { };
}
void GenerateBeam::notify(ProgramEvent) {
    // Empty.
}
void GenerateBeam::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.rotate(
        angle(player_direction, massive_beam_generate_sprite_sheet.orientation),
        player_circle.position
    );
    states.transform.translate(
        player_circle.position + player_direction * 2.0f * player_circle.R
    );

    target.draw(massive_beam_generated, states);
}