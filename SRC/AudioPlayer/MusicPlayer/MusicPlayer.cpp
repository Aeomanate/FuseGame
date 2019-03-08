// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 02.03.2019.
//

#include <algorithm>
#include <chrono>
#include "MusicPlayer.hpp"
#include "../../Utility/IndexDataFile/IndexDataFile.hpp"
#include "../../Utility/Math/Random/Random.hpp"

MusicPlayer::MusicPlayer()
: music_names {
    "BackgroundMusic (1)",
    "BackgroundMusic (10)",
    "BackgroundMusic (2)",
    "BackgroundMusic (3)",
    "BackgroundMusic (4)",
    "BackgroundMusic (5)",
    "BackgroundMusic (6)",
    "BackgroundMusic (7)",
    "BackgroundMusic (8)",
    "BackgroundMusic (9)",
  }
, special_music_names {
    "SpecialMusic (2)",
    "SpecialMusic (1)"
  }
{
   for(auto const& music_name: music_names) {
       music_sources[music_name] = loadFromFileRawData(music_name);
   }
   
   playUniqueRand();
}

ProgramEvents MusicPlayer::update() {
    if(isMusicStopped()) {
        playUniqueRand();
    }
    
    bool is_secret_music_start = cur_music.getStatus() == sf::Music::Status::Stopped;
    bool is_secret_music_already_started = music_names.size() == 1;
    if(is_march8_mode && is_secret_music_start && !is_secret_music_already_started) {
        music_names.erase(music_names.begin());
    }
    
    return eventsWalker( RUN_FOR_ALL_OF_RECEIVED_EVENTS {
        if(std::holds_alternative<MusicPlay>(e)) {
            cur_music.play();
        }
        if(std::holds_alternative<MusicStop>(e)) {
            cur_music.stop();
        }
        if(std::holds_alternative<MusicPause>(e)) {
            cur_music.pause();
        }
    
    
        if(std::holds_alternative<Martch8Start>(e)) {
            music_names = special_music_names;
            cur_music.stop();
            playlist.clear();
            for(auto const& music_name: music_names) {
                music_sources[music_name] = loadFromFileRawData(music_name);
            }
        }
        if(std::holds_alternative<Martch8End>(e)) {
            // Nothing, game should be close before Martch8End is needed.
        }
    });
}
void MusicPlayer::notify(ProgramEvent e) {
    received_events.push_back(e);
}
void MusicPlayer::draw(sf::RenderTarget&, sf::RenderStates) const {
    // Empty.
}


void MusicPlayer::playUniqueRand() {
    if(playlist.empty()) {
        updatePlaylist();
        if(!is_march8_mode) {
            std::shuffle(playlist.begin(), playlist.end(), random);
        }
    }
    
    if(openMusic(playlist.back())) {
        cur_music.setVolume(50);
        cur_music.play();
        playlist.pop_back();
    } else {
        std::cerr << "Failed to load music from memory";
    }
    
}

void MusicPlayer::updatePlaylist() {
    for(NameIterator name = music_names.begin(); name != music_names.end(); ++name) {
        playlist.push_back(name);
    }
}

bool MusicPlayer::openMusic(NameIterator name_iterator) {
    std::vector<char> const &selected_music = music_sources[*name_iterator];
    return cur_music.openFromMemory(selected_music.data(), selected_music.size());
}
bool MusicPlayer::isMusicStopped() const {
    return cur_music.getStatus() == sf::Music::Status::Stopped;
}
bool MusicPlayer::isMusicPaused() const {
    return cur_music.getStatus() == sf::Music::Status::Paused;
}
