//
// Created by Lyosha12 on 27.07.2018.
//

#ifndef SNAKE_SOUNDPLAYER_HPP
#define SNAKE_SOUNDPLAYER_HPP

#include <map>
#include <SFML/Audio.hpp>
#include <boost/filesystem.hpp>
#include "../../Utility/GameObject.hpp"
namespace fs = boost::filesystem;

class UncontrolledSound: public GameObject {
  public:
    UncontrolledSound(sf::Sound& sound);
    
    ProgramEvents update() override;
    void notify(ProgramEvent) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
  private:
    sf::Sound sound;
};

class SoundPlayer: public GameObject {
    struct SoundStorage {
        bool is_controlled;
        std::vector<char> sound_source;
        sf::SoundBuffer buffer;
        sf::Sound sound_template;
    };
    
  public:
    SoundPlayer();
    
    ProgramEvents update() override;
    void notify(ProgramEvent e) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
  private:
    std::map<std::string, SoundStorage> sounds;
};


#endif //SNAKE_SOUNDPLAYER_HPP
