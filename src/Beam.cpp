#include <math.h>
#include <iostream>
#include <algorithm>
#include "Beam.h"
#define INF INT32_MAX

Beam::Beam(int x, int y, float angle) : Line(x, y, angle, 2){}

void Beam::checkCollision(const std::vector<Wall>& walls)
{
    //setting second point to be outside the screen
    if (secondPoint.x < WINDOW_WIDTH && secondPoint.x > 0 && secondPoint.y < WINDOW_HEIGHT && secondPoint.y > 0)
        this->SetLength(WINDOW_WIDTH + WINDOW_HEIGHT);
    

    // calculating coefficients for equation y = kx + b
    // if two points are on one parallel to y line, assign k = INF
    float k_beam = (secondPoint.x - firstPoint.x) == 0 ? INF : (secondPoint.y - firstPoint.y) / (secondPoint.x - firstPoint.x);
    float b_beam = (secondPoint.x - firstPoint.x) == 0 ? -INF : firstPoint.y - k_beam * firstPoint.x;

    for (auto& wall : walls)
    {
        float k_wall = (wall.secondPoint.x - wall.firstPoint.x) == 0 ? INF : (wall.secondPoint.y - wall.firstPoint.y) / (wall.secondPoint.x - wall.firstPoint.x);
        float b_wall = (wall.secondPoint.x - wall.firstPoint.x) == 0 ? -INF : wall.firstPoint.y - k_wall * wall.firstPoint.x;
        Point intercept(0, 0);

        if (k_beam == INF)
        {
            if (k_wall != INF)
            {
                intercept.x = firstPoint.x;
                intercept.y = k_wall * intercept.x + b_wall;
            }
            else
            {
                auto temp_distance = std::min({ firstPoint.DistanceTo(wall.secondPoint),
                                                firstPoint.DistanceTo(wall.firstPoint),
                                                firstPoint.DistanceTo(secondPoint) });
                this->SetLength(temp_distance);
            }
        }
        else
        {
            if (k_wall != INF)
            {
                intercept.x = (b_wall - b_beam) / (k_beam - k_wall);
                intercept.y = k_beam * intercept.x + b_beam;
            }
            else
            {
                intercept.x = wall.firstPoint.x;
                intercept.y = k_beam * intercept.x + b_beam;
            }
        }

        if (this->Contains(intercept) && wall.Contains(intercept))
            this->SetLength(firstPoint.DistanceTo(intercept));

    }
    
}

Beam::~Beam()
{
}