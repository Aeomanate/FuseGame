// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 27.07.2018.
//

#include "AudioPlayer.hpp"

ProgramEvents AudioPlayer::update() {
    ProgramEvents generated_events;
    append(generated_events, music_player.update());
    append(generated_events, sound_player.update());
    
    return generated_events;
}
void AudioPlayer::notify(ProgramEvent e) {
    music_player.notify(e);
    sound_player.notify(e);
}
void AudioPlayer::draw(sf::RenderTarget&, sf::RenderStates) const {
    // Empty.
}