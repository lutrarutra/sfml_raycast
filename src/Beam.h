#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Line.h"
#include "Wall.h"

class Beam : public Line
{
public:
    Beam(int x, int y, float angle);
    void checkCollision(const std::vector<Wall>& walls);
    ~Beam();

private:
};

