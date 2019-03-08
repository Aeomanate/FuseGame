//
// Created by Lyosha12 on 02.03.2019.
//

#ifndef FUSEGAME_AUDIOPLAYER_HPP
#define FUSEGAME_AUDIOPLAYER_HPP

#include "MusicPlayer/MusicPlayer.hpp"
#include "SoundPlayer/SoundPlayer.hpp"

class AudioPlayer: public GameObject {
  public:
    ProgramEvents update() override;
    void notify(ProgramEvent e) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
  private:
    MusicPlayer music_player;
    SoundPlayer sound_player;
};


#endif //FUSEGAME_AUDIOPLAYER_HPP
