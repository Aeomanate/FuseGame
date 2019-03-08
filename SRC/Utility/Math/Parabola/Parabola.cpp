// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 08.03.2019.
//

#include "Parabola.hpp"


// http://econom.misis.ru/S/Hel/Matem/Para_3t.htm
Parabola::Parabola(float x1, float y1, float x2, float y2, float x3, float y3)
: x1(x1) , y1(y1)
, x2(x2) , y2(y2)
, x3(x3) , y3(y3)

, a(( y3 - (x3 * (y2 - y1) + x2*y1 - x1*y2) / (x2 - x1) ) / (x3 * (x3 - x1 - x2) + x1 * x2))
, b((y2 - y1) / (x2 - x1) - a*(x1 + x2))
, c((x2*y1 - x1*y2) / (x2 - x1) + a*x1*x2)
{ }

float Parabola::ordinate(float abscissa) const {
    return a*abscissa*abscissa + b*abscissa + c;
}