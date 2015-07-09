#pragma once

#include "Vector2.h"

namespace se
{
    class Rectangle
    {
    public:

        float top;
        float bottom;
        float left;
        float right;

    public:

        Rectangle();
        Rectangle(float top, float bottom, float left, float right);
        ~Rectangle();

    public:

        bool overlap(Rectangle rect);
        bool contains(Vector2 point);
        void move(se::Vector2 translation);
    };
}
