#pragma once

#include <vector>
#include "Vector2.h"

namespace se
{
    class Polygon
    {
    private:

        std::vector<Vector2> points;
        Vector2 position;
        float rotation;
        Vector2 size;

    public:

        Polygon();
        Polygon(std::vector<Vector2> points);
        ~Polygon();

    public:

        bool overlap(Polygon& other);
        const std::vector<Vector2>& getPoints();
        void setPosition(Vector2 position);
        void move(Vector2 movement);
        void setRotation(float rotation);
        void rotate(float rotation);
        void setScale(Vector2 scale);
        void scale(Vector2 factor);
    };
}