#pragma once

namespace se
{
    class Vector2
    {
    public:

        float x;
        float y;

    public:

        Vector2()
            : x(0)
            , y(0)
        {

        }

        Vector2(float x, float y)
            : x(x)
            , y(y)
        {

        }

        Vector2(int x, int y)
            : x((float)x)
            , y((float)y)
        {

        }

        inline Vector2& operator+=(const Vector2& rhs)
        {
            this->x += rhs.x;
            this->y += rhs.y;

            return *this;
        }

        inline Vector2& operator-=(const Vector2& rhs)
        {
            this->x -= rhs.x;
            this->y -= rhs.y;

            return *this;
        }

        inline Vector2& operator*=(const Vector2& rhs)
        {
            this->x *= rhs.x;
            this->y *= rhs.y;

            return *this;
        }

        inline Vector2& operator*=(const float rhs)
        {
            this->x *= rhs;
            this->y *= rhs;

            return *this;
        }

        inline Vector2& operator/=(const Vector2& rhs)
        {
            this->x /= rhs.x;
            this->y /= rhs.y;

            return *this;
        }

        inline Vector2& operator/=(const float rhs)
        {
            this->x /= rhs;
            this->y /= rhs;

            return *this;
        }
    };
}