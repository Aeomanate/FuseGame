//
// Created by Lyosha12 on 24.02.2019.
//

#ifndef FUSEGAME_OBSERVER_HPP
#define FUSEGAME_OBSERVER_HPP

#include <queue>
#include "ProgramEvents/ProgramEvents.hpp"

class Observer {
  public:
    virtual void notify(ProgramEvent program_event) = 0;
  
  protected:
    ProgramEvents received_events;
};


#endif //FUSEGAME_OBSERVER_HPP
