// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 07.03.2019.
//

#include <cmath>
#include "Line.hpp"

Line::Line(float A, float B, float C)
    : A(A), B(B), C(C)
{ }

Line::Line(sf::Vector2f A, sf::Vector2f B)
    : A(B.y - A.y)
    , B(B.x - A.x)
    , C(-(B.y - A.y)*A.x + (B.x - A.x)*A.y)
{ }
float Line::ordinate(float abscissa) const {
    return (A*abscissa + C) / (B);
}

float Line::distance(sf::Vector2f point) const {
    return static_cast<float>(
        std::abs((A*point.x + B*point.y + C)) / sqrt(A*A + B*B)
    );
}