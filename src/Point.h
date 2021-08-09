#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class Point : public sf::Vector2f
{
public:
    inline float DistanceTo(const Point& other) const
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
    inline static float DistanceBetween(const Point& first, const Point& second)
    {      
        return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
    }
    Point(float x_, float y_) : sf::Vector2f(x_, y_){}
    Point()
    {
        x = 0; y = 0;
    }
};
