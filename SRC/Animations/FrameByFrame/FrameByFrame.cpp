// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 03.03.2019.
//

#include "FrameByFrame.hpp"
#include "../../Utility/WindowForTests/WindowForTests.hpp"

FrameByFrame::FrameByFrame(
    MemoryTextureStorage const& texture_storage,
    Timer<> frame_interval,
    int count_repeats
)
: texture_storage(texture_storage)
, frame_interval(frame_interval)
, frame(texture_storage.sprite)
, count_repeats(count_repeats)
{
    frame.setOrigin(
        texture_storage.frame_size.x / 2.0f,
        texture_storage.frame_size.y / 2.0f
    );
    update();
}

FrameByFrame::FrameByFrame(
    MemoryTextureStorage const& texture_storage,
    size_t frames_per_second,
    int count_repeats
)
: FrameByFrame (
    texture_storage,
    std::chrono::milliseconds(static_cast<size_t>(1000.0 / frames_per_second)),
    count_repeats
  )
{ }


ProgramEvents FrameByFrame::update() {
    if(frame_interval.resetCheckIntervalExpired()) {
        calcNextFrame();
        updateFrame();
    }
    
    return { };
}
void FrameByFrame::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(frame, states);
}

bool FrameByFrame::isAnimationStopped() const {
    return current_repeat == count_repeats;
}
void FrameByFrame::calcNextFrame() {
    size_t x_frame_next = cur_frame.x + 1;
    cur_frame.x = x_frame_next % texture_storage.count_frames.x;
    
    size_t y_frame_increment = x_frame_next / texture_storage.count_frames.x; // 0 or 1.
    size_t y_next = cur_frame.y + y_frame_increment;
    cur_frame.y = y_next % texture_storage.count_frames.y;
    
    if(count_repeats >= 0) {
        bool is_repeated = y_next / texture_storage.count_frames.y == 1;
        if(is_repeated) {
            if(current_repeat == count_repeats) {
                return;
            } else {
                ++current_repeat;
            }
        }
    }
}
void FrameByFrame::updateFrame() {
    if(!isAnimationStopped()) {
        frame.setTextureRect(
            sf::IntRect(
                sf::Vector2i(
                    cur_frame.x * texture_storage.frame_size.x,
                    cur_frame.y * texture_storage.frame_size.y
                ),
                sf::Vector2i(
                    texture_storage.frame_size.x,
                    texture_storage.frame_size.y
                )
            )
        );
    }
}