#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Beam.h"

class Source
{
public:
    Source(int x, int y, int beamCount);
    ~Source();
    void draw(sf::RenderWindow &window) const;
    void move(int x, int y);
    void checkWalls(const std::vector<Wall> &walls);

private:
    int m_x, m_y, m_beamCount;
    std::vector<Beam> m_beams;
};