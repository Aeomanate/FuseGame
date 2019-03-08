//
// Created by Lyosha12 on 24.02.2019.
//


#ifndef FUSEGAME_GAMEOBJECT_HPP
#define FUSEGAME_GAMEOBJECT_HPP

#include <memory>
#include <functional>
#include "Updateable.hpp"
#include "Observer.hpp"
#include <SFML/Graphics.hpp>

class GameObject
    : public Updateable
    , public Observer
    , public sf::Drawable
{
  public:
    GameObject(): object_id(count_objects++) { }
    
  protected:
    // * Almost each of derive of GameObject must handle program events.
    //   This chapter of code is "standard" of handle events.
    // * So those who need to handle programEvents
    //   may just use this generalized code of walk and handle on stored events
    //   via send own handler-function via macros below to eventsWalker.
    using Visitor = std::function<void(ProgramEvents&, ProgramEvent const&)>;
    inline ProgramEvents eventsWalker(Visitor events_handler) {
        ProgramEvents generated_events;
        
        for(ProgramEvent const& e: received_events) {
            events_handler(generated_events, e);
        }
        received_events.clear();
    
        return generated_events;
    }
    
  public:
    static inline size_t count_objects = 0;
    size_t object_id;
};

#define RUN_FOR_ALL_OF_RECEIVED_EVENTS \
[&] ([[maybe_unused]] ProgramEvents& generated_events, ProgramEvent const& e) -> void


#endif //FUSEGAME_GAMEOBJECT_HPP
