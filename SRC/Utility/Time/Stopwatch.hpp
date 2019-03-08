//
// Created by Lyosha12 on 01.03.2019.
//

#ifndef FUSEGAME_STOPWATCH_HPP
#define FUSEGAME_STOPWATCH_HPP

#include <string>
#include <type_traits>
#include <stdexcept>
#include <chrono>

using namespace std::chrono_literals;

template <class Clock = std::chrono::steady_clock>
class Stopwatch {
    using TimePoint = std::chrono::time_point<Clock, std::chrono::nanoseconds>;
    
  public:
    void start() {
        start_time = Clock::now();
        measured_interval = { };
        finish_time = { };
    }
    void stop() {
        if(start_time == TimePoint { }) {
            return;
            throw std::logic_error("Trying to stop stopped stopwatcher");
        }
        
        finish_time = Clock::now();
        measured_interval = finish_time - start_time;
        finish_time = start_time = TimePoint { };
    }
    
    bool isEnable() const {
        return start_time != TimePoint { };
    }
    
    
    template <class IntervalType>
    IntervalType getInterval() const {
        std::chrono::nanoseconds interval;
        
        if(start_time == TimePoint { }) {
            interval = measured_interval;
        } else if(finish_time == TimePoint{ }) {
            interval = Clock::now() - start_time;
        } else {
            interval = finish_time - start_time;
        }
        
        return std::chrono::duration_cast<IntervalType>(interval);
    }
    template <class IntervalType, class SizeType>
    SizeType getCount() const {
        return static_cast<SizeType>(getInterval<IntervalType>().count());
    }
    
    
    template <class IntervalType>
    std::wstring interval_to_string(uintmax_t nanos) const {
        uintmax_t rest = nanos % 1000; // Count nanoseconds.
        
        if constexpr(is_same<IntervalType, std::chrono::nanoseconds>)
            return std::to_wstring(rest) + L"ns";
    
        rest = (nanos /= 1000) % 1000; // Count microseconds;
        if(is_same<IntervalType, std::chrono::microseconds>)
            return std::to_wstring(rest) + L"mcs";
        
        rest = (nanos /= 1000) % 1000; // Count milliseconds;
        if(is_same<IntervalType, std::chrono::milliseconds>)
            return std::to_wstring(rest) + L"ms";
        
        rest = (nanos /= 1000) % 60; // Count seconds;
        if(is_same<IntervalType, std::chrono::seconds>     )
            return std::to_wstring(rest) + L"s";
        
        rest = (nanos /= 60) % 60; // Count minutes;
        if(is_same<IntervalType, std::chrono::minutes>     )
            return std::to_wstring(rest) + L"m";
    
        rest = (nanos /= 60) % 24; // Count hours;
        if(is_same<IntervalType, std::chrono::hours>       )
            return std::to_wstring(rest) + L"h";
        
        rest = (nanos /= 24); // Count days;
        if(is_same<IntervalType, std::chrono::hours>       )
            return std::to_wstring(rest) + L"d";
        
        throw std::logic_error("Requested time type is not a time");
    }
    
    template <class... TimeUnits>
    std::wstring getText() const {
        uintmax_t nanos = getCount<std::chrono::nanoseconds, uintmax_t>();
        return ((interval_to_string<TimeUnits>(nanos) + L" ") + ... + L"");
    }
    
  private:
    TimePoint start_time = { }, finish_time = { };
    std::chrono::nanoseconds measured_interval;
    
    template <class A, class B>
    inline static bool constexpr is_same = std::is_same<A, B>::value;
};


#endif //FUSEGAME_STOPWATCH_HPP
