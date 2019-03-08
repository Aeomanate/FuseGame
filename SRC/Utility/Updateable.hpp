//
// Created by Lyosha12 on 24.02.2019.
//

#ifndef FUSEGAME_UPDATABLE_HPP
#define FUSEGAME_UPDATABLE_HPP

#include <queue>
#include <list>
#include "ProgramEvents/ProgramEvents.hpp"

class Updateable {
  public:
    [[nodiscard]] virtual ProgramEvents update() = 0;
    inline virtual ~Updateable() { };
};


#endif //FUSEGAME_UPDATABLE_HPP
