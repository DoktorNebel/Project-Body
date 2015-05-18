#pragma once

#include <vector>
#include "Vector2.h"

namespace se
{
    class Polygon
    {
    public:

        std::vector<se::Vector2> points;

    public:

        Polygon(std::vector<se::Vector2> points);
        ~Polygon();

    public:

        bool overlap(Polygon& other);
    };
}