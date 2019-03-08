//
// Created by Lyosha12 on 01.03.2019.
//

#ifndef FUSEGAME_TIMER_HPP
#define FUSEGAME_TIMER_HPP

#include <stdexcept>
#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

template <class Clock = std::chrono::steady_clock>
class Timer {
  public:
    using InternalTimeUnit = std::chrono::nanoseconds;
    
  public:
    template <class IncomingTimeUnit = InternalTimeUnit>
    Timer(IncomingTimeUnit interval = IncomingTimeUnit(0))
    : interval(convert(interval))
    , starting_point(Clock::now() - interval)
    { }
    
    template <class IncomingTimeUnit, class Integral>
    void setInterval(Integral interval) {
        this->interval = convert(IncomingTimeUnit(interval));
    }
    
    template <class ResultTimeUnit = InternalTimeUnit>
    ResultTimeUnit getInterval() const {
        return convert<ResultTimeUnit>(interval);
    }
    
    bool resetCheckIntervalExpired() {
        if(is_paused) {
            std::cerr << "Trying to check Timer when it has paused.";
        }
        
        bool is_expire = Clock::now() - starting_point > interval;
        if(is_expire) {
            this->reset();
        }
        return is_expire;
    }
    bool checkIntervalExpired() const {
        if(is_paused) {
            std::cerr << "Trying to check Timer when it has paused.";
        }
        bool is_expire = Clock::now() - starting_point > interval;
        return is_expire;
    }

    
    void reset() {
        starting_point = Clock::now();
    }
    void pause() {
        residual_interval = Clock::now() - starting_point;
        is_paused = true;
    }
    void resume() {
        starting_point = Clock::now() - residual_interval;
        is_paused = false;
    }
    
  private:
    template <class ResultTimeUnit = InternalTimeUnit, class IncomingTimeUnit>
    ResultTimeUnit convert(IncomingTimeUnit incoming_interval) const {
        return std::chrono::duration_cast<ResultTimeUnit> (incoming_interval);
    }
  
  private:
    InternalTimeUnit interval;
    InternalTimeUnit residual_interval; // Остаток интервала при паузе.
    typename Clock::time_point starting_point;
    bool is_paused = false;
};


#endif // FUSEGAME_TIMER_HPP
