#include <math.h>
#include <iostream>
#include <algorithm>
#include "Beam.h"


Beam::Beam(int x, int y, float angle) : Line(x, y, angle, 2){}

void Beam::checkCollision(const std::vector<Wall>& walls)
{
    //setting second point to be outside the screen
    if (secondPoint.x < WINDOW_WIDTH && secondPoint.x > 0 && secondPoint.y < WINDOW_HEIGHT && secondPoint.y > 0)
        this->SetLength(WINDOW_WIDTH + WINDOW_HEIGHT);
    
    // calculating coefficients for equation y = kx + b
    // if two points are on one parallel to y line, assign k = INF
    sf::Vector2f kbCoefs = FindKBCoeffs();
    float k_beam = kbCoefs.x;
    float b_beam = kbCoefs.y;

    for (auto& wall : walls)
    {
        sf::Vector2f wallKBCoefs = wall.FindKBCoeffs();
        float k_wall = wallKBCoefs.x;
        float b_wall = wallKBCoefs.y;

        Point intercept = FindInterception(wall);
        
        if ( intercept.x == INF )
            continue;

        if (this->Contains(intercept) && wall.Contains(intercept))
            this->SetLength(firstPoint.DistanceTo(intercept));
    }
    
}

Beam::~Beam()
{
}