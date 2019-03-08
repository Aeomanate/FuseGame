// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 07.03.2019.
//

#include <cmath>
#include "Circle.hpp"
#include "../Vectors/Vectors.hpp"

Circle::Circle(float R, sf::Vector2f position)
    : R(R)
    , position(position)
{ }

Circle::Intersection::Intersection(int count, sf::Vector2f A, sf::Vector2f B)
    : count(count)
    , A(A)
    , B(B)
{ }
bool Circle::Intersection::isExists() const {
    return count > 0;
}

Circle::Intersection Circle::intersection(Circle const& other) const {
    // http://e-maxx.ru/algo/circles_intersection
    float const& x2 = other.position.x - position.x;
    float const& y2 = other.position.y - position.y;
    
    float const& r1 = R;
    float const& r2 = other.R;
    
    float A = -2*x2;
    float B = -2*y2;
    float C = x2*x2 + y2*y2 + r1*r1 - r2*r2;
    
    return intersection(Line(A, B, C));
}
Circle::Intersection Circle::intersection(Line const& line) const {
    // http://e-maxx.ru/algo/circle_line_intersection
    float const& a = line.A;
    float const& b = line.B;
    float const& c = line.C;
    float a2pb2 = a*a+b*b;
    float const& r = R;
    
    float x0 = -a*c/a2pb2;
    float y0 = -b*c/a2pb2;
    float EPS = 1e-3;
    
    bool zero = c*c > r*r*a2pb2 + EPS;
    bool one = std::fabs(c*c - r*r*a2pb2) < EPS;
    bool two = !zero && !one;
    
    float d = r*r - c*c/a2pb2;
    float mult = std::sqrt( d / a2pb2 );
    Intersection ans {
        2*two + one,
        {
            x0 + b * mult + position.x,
            y0 - a * mult + position.y
        },
        {
            x0 - b * mult + position.x,
            y0 + a * mult + position.y
        }
    };
    
    return ans;
}
bool Circle::isInside(sf::Vector2f point) const {
    return length(point - position) < R;
}

