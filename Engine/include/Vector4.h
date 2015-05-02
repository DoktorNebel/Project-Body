#pragma once

#include "Vector3.h"

namespace se
{
    class Vector4
    {
    public:

        float x;
        float y;
        float z;
        float w;

    public:

        Vector4()
            : x(0)
            , y(0)
            , z(0)
            , w(1)
        {

        }

        Vector4(float x, float y, float z)
            : x(x)
            , y(y)
            , z(z)
            , w(1)
        {

        }

        Vector4(float x, float y, float z, float w)
            : x(x)
            , y(y)
            , z(z)
            , w(w)
        {

        }

        Vector4(Vector3 xyz, float w)
            : x(xyz.x)
            , y(xyz.y)
            , z(xyz.z)
            , w(w)
        {

        }

        inline Vector4& operator+=(const Vector4& rhs)
        {
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            this->w += rhs.w;

            return *this;
        }

        inline Vector4& operator-=(const Vector4& rhs)
        {
            this->x -= rhs.x;
            this->y -= rhs.y;
            this->z -= rhs.z;
            this->w -= rhs.w;

            return *this;
        }

        inline Vector4& operator*=(const Vector4& rhs)
        {
            this->x *= rhs.x;
            this->y *= rhs.y;
            this->z *= rhs.z;
            this->w *= rhs.w;

            return *this;
        }

        inline Vector4& operator*=(const float rhs)
        {
            this->x *= rhs;
            this->y *= rhs;
            this->z *= rhs;
            this->w *= rhs;

            return *this;
        }

        inline Vector4& operator/=(const Vector4& rhs)
        {
            this->x /= rhs.x;
            this->y /= rhs.y;
            this->z /= rhs.z;
            this->w /= rhs.w;

            return *this;
        }

        inline Vector4& operator/=(const float rhs)
        {
            this->x /= rhs;
            this->y /= rhs;
            this->z /= rhs;
            this->w /= rhs;

            return *this;
        }
    };
}