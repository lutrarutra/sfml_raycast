#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Beam.h"

class Source
{
public:
    Source(int x, int y, int beamCount);
    ~Source();
    void Draw(sf::RenderWindow &window) const;
    void Move(Point destination);
    void checkWalls(const std::vector<Wall> &walls);

private:
    Point m_point;
    int m_beamCount;
    std::vector<Beam> m_beams;
};