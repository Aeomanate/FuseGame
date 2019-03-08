//
// Created by Lyosha12 on 02.03.2019.
//

#ifndef FUSEGAME_MUSICPLAYER_HPP
#define FUSEGAME_MUSICPLAYER_HPP


#include <map>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>
#include "../../Utility/Time/Timer.hpp"
#include "../../Utility/GameObject.hpp"


// For long music.
class MusicPlayer: public GameObject {
    using NameIterator = std::vector<std::string>::const_iterator;
  public:
    MusicPlayer();
    
    ProgramEvents update() override;
    void notify(ProgramEvent e) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
  private:
    // From memory (from data.bin) load music names what will be
    // randomly sorted and plays by one in cycle.
    void playUniqueRand();
    
    void updatePlaylist();
    bool openMusic(NameIterator name_iterator);
    
    bool isMusicStopped() const;
    bool isMusicPaused() const;
  
  private:
    std::map<std::string, std::vector<char>> music_sources;
    std::vector<std::string> music_names;
    std::vector<std::string> special_music_names;
    std::vector<NameIterator> playlist;
    sf::Music cur_music;
    
    bool is_march8_mode = false;
};


#endif //FUSEGAME_MUSICPLAYER_HPP
