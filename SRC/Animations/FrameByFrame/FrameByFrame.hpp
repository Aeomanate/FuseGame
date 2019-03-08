//
// Created by Lyosha12 on 03.03.2019.
//

#ifndef FUSEGAME_FRAMEBYFRAME_HPP
#define FUSEGAME_FRAMEBYFRAME_HPP

#include <chrono>
using namespace std::chrono_literals;
#include "../../Utility/GameObject.hpp"
#include "../../Utility/ProgramEvents/ProgramEvents.hpp"
#include "../../Utility/Time/Timer.hpp"
#include "../../Utility/MemoryTextureStorage/MemoryTextureStorage.hpp"



class FrameByFrame: public sf::Drawable, public Updateable {
  public:
    using FrameInterval = std::chrono::milliseconds;
    
  public:
    FrameByFrame(
        MemoryTextureStorage const& texture_storage,
        Timer<> frame_interval,
        int count_repeats = 1 // < 0 == endless
    );
    FrameByFrame(
        MemoryTextureStorage const& texture_storage,
        size_t frames_per_second,
        int count_repeats = 1 // < 0 == endless
    );
    
    ProgramEvents update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    bool isAnimationStopped() const;
    
  private:
    void calcNextFrame();
    void updateFrame();
    
  private:
    MemoryTextureStorage const& texture_storage;
    Timer <> frame_interval;
    
    sf::Vector2u cur_frame = { 0, 0 };
    sf::Sprite frame;
    
    int count_repeats;
    int current_repeat = 0;
};


#endif //FUSEGAME_FRAMEBYFRAME_HPP
