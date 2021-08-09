#pragma once

#include <SFML/Graphics.hpp>

#include "Line.h"

class Wall : public Line
{
public:
    Wall(int x1, int y1, int x2, int y2);
    inline float GetAngle() const { return m_angle; };
    ~Wall();

private:

};