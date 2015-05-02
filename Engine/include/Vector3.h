#pragma once

namespace se
{
    class Vector3
    {
    public:

        float x;
        float y;
        float z;

    public:

        Vector3()
            : x(0)
            , y(0)
            , z(0)
        {

        }

        Vector3(float x, float y, float z)
            : x(x)
            , y(y)
            , z(z)
        {

        }

        inline Vector3& operator+=(const Vector3& rhs)
        {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;

            return *this;
        }

        inline Vector3& operator-=(const Vector3& rhs)
        {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;

            return *this;
        }

        inline Vector3& operator*=(const Vector3& rhs)
        {
            this->x *= rhs.x;
            this->y *= rhs.y;
            this->z *= rhs.z;

            return *this;
        }

        inline Vector3& operator*=(const float rhs)
        {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;

            return *this;
        }

        inline Vector3& operator/=(const Vector3& rhs)
        {
            this->x /= rhs.x;
            this->y /= rhs.y;
            this->z /= rhs.z;

            return *this;
        }

        inline Vector3& operator/=(const float rhs)
        {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;

            return *this;
        }
    };
}