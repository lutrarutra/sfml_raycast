#pragma once

#include "proj_data.h"
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

