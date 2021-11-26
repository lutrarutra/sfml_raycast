#pragma once
#include "proj_data.h"
#include "Beam.h"

class Source
{
public:
    Source(int x, int y, int beamCount);
    Source();
    ~Source();
    void Draw(sf::RenderWindow &window) const;
    void Move(Point destination);
    void checkWalls(const std::vector<Wall> &walls);
    void SetBeamCount(int count);

    void SetBeamColor( sf::Color& color );

private:

private:
    static constexpr int DEFAULT_BEAM_COUNT = 720;
    Point m_point;
    int m_beamCount;
    std::vector<Beam> m_beams;
};