//
// Created by Lyosha12 on 08.03.2019.
//

#ifndef FUSEGAME_PARABOLA_HPP
#define FUSEGAME_PARABOLA_HPP

#include <SFML/System/Vector2.hpp>

struct Parabola {
    // http://econom.misis.ru/S/Hel/Matem/Para_3t.htm
    Parabola(float x1, float y1, float x2, float y2, float x3, float y3);
    Parabola() = default;
  
    float ordinate(float abscissa) const;
    
    float x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
    float a = 0, b = 0, c = 0;
};


#endif // FUSEGAME_PARABOLA_HPP
