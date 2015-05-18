#include "Polygon.h"

namespace se
{
    Polygon::Polygon(std::vector<se::Vector2> points)
        : points(points)
    {

    }


    Polygon::~Polygon()
    {

    }


    bool Polygon::overlap(Polygon& other)
    {
        return false;
    }
}