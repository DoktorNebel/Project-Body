#pragma once

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

        Rectangle(float top, float bottom, float left, float right);
        ~Rectangle();

    public:

        bool overlap(Rectangle rect);
    };
}
