// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 27.07.2018.
//

#include <iostream>
#include "SoundPlayer.hpp"
#include "../../Utility/IndexDataFile/IndexDataFile.hpp"

UncontrolledSound::UncontrolledSound(sf::Sound& sound)
: sound(sound)
{
    this->sound.play();
}

ProgramEvents UncontrolledSound::update() {
    if(sound.getStatus() == sf::Sound::Status::Stopped) {
        return { DestructedObject( { this }) };
    }

    return { };
}
void UncontrolledSound::notify(ProgramEvent) { }
void UncontrolledSound::draw(sf::RenderTarget&, sf::RenderStates) const {  }




SoundPlayer::SoundPlayer()
: sounds {
    { "Bomb1"                     , { false, { }, { }, { } } },
    { "Bomb2"                     , { false, { }, { }, { } } },
    { "Bomb3"                     , { false, { }, { }, { } } },
    { "Bomb4"                     , { false, { }, { }, { } } },
    { "EnemyDeath1"               , { false, { }, { }, { } } },
    { "EnemyDeath2"               , { false, { }, { }, { } } },
    { "EnemyDeath3"               , { false, { }, { }, { } } },
    { "EnemyShot"                 , { false, { }, { }, { } } },
    { "MassiveAccumulation"       , { true , { }, { }, { } } },
    { "MassiveCancelAccumulation" , { true , { }, { }, { } } },
    { "MassiveExplosion"          , { false, { }, { }, { } } },
    { "MassiveShot"               , { false, { }, { }, { } } },
    { "Pararam"                   , { false, { }, { }, { } } },
    { "PlayerDeathSound"          , { false, { }, { }, { } } },
    { "PlayerShot"                , { false, { }, { }, { } } },
    { "TakeDamage"                , { false, { }, { }, { } } },
}
{
    for(auto& node: sounds) {
        SoundStorage& storage = node.second;
        std::vector<char>& sound_source = storage.sound_source;
        sound_source = loadFromFileRawData(node.first);
        
        storage.buffer.loadFromMemory(sound_source.data(), sound_source.size());
        storage.sound_template.setBuffer(storage.buffer);
    }
    
    
}

ProgramEvents SoundPlayer::update() {
    return eventsWalker( RUN_FOR_ALL_OF_RECEIVED_EVENTS {
        if(std::holds_alternative<SoundStop>(e)) {
            std::string const& sound_name = std::get<SoundStop>(e).sound_name;
            try {
                SoundStorage& storage = sounds.at(sound_name);
                if(storage.is_controlled) {
                    storage.sound_template.stop();
                }
            } catch (std::exception const& e) {
                throw std::logic_error("Sound name " + sound_name + " are wrong");
            }
        }
    
        if(std::holds_alternative<SoundPlay>(e)) {
            std::string const& sound_name = std::get<SoundPlay>(e).sound_name;
            try {
                SoundStorage& storage = sounds.at(sound_name);
                
                if(storage.is_controlled) {
                    if(storage.sound_template.getStatus() == sf::Sound::Status::Stopped)
                        storage.sound_template.play();
                } else {
                    generated_events.push_back( ConstructedObject {
                       new UncontrolledSound (storage.sound_template)
                    });
                }
            } catch (std::exception const& e) {
                throw std::logic_error("Sound name " + sound_name + " are wrong");
            }
        }
    });
}
void SoundPlayer::notify(ProgramEvent e) {
    received_events.push_back(e);
}
void SoundPlayer::draw(sf::RenderTarget&, sf::RenderStates) const { }
