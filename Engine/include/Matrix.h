#pragma once

#include "Vector4.h"

namespace se
{
    union Matrix
    {
    private:

        float data[16];

    public:

        struct
        {
            float v00;
            float v10;
            float v20;
            float v30;

            float v01;
            float v11;
            float v21;
            float v31;

            float v02;
            float v12;
            float v22;
            float v32;

            float v03;
            float v13;
            float v23;
            float v33;
        };


    public:

        inline Matrix& operator+=(Matrix rhs)
        {
            for (int i = 0; i < 16; ++i)
            {
                (*this)[i] += rhs[i];
            }

            return *this;
        }

        inline Matrix& operator-=(Matrix rhs)
        {
            for (int i = 0; i < 16; ++i)
            {
                (*this)[i] -= rhs[i];
            }

            return *this;
        }

        inline Matrix& operator*=(Matrix rhs)
        {
            this->v00 = this->v00 * rhs.v00 + this->v01 * rhs.v10 + this->v02 * rhs.v20 + this->v03 * rhs.v30;
            this->v01 = this->v00 * rhs.v01 + this->v01 * rhs.v11 + this->v02 * rhs.v21 + this->v03 * rhs.v31;
            this->v02 = this->v00 * rhs.v02 + this->v01 * rhs.v12 + this->v02 * rhs.v22 + this->v03 * rhs.v32;
            this->v03 = this->v00 * rhs.v03 + this->v01 * rhs.v13 + this->v02 * rhs.v23 + this->v03 * rhs.v33;

            this->v10 = this->v10 * rhs.v00 + this->v11 * rhs.v10 + this->v12 * rhs.v20 + this->v13 * rhs.v30;
            this->v11 = this->v10 * rhs.v01 + this->v11 * rhs.v11 + this->v12 * rhs.v21 + this->v13 * rhs.v31;
            this->v12 = this->v10 * rhs.v02 + this->v11 * rhs.v12 + this->v12 * rhs.v22 + this->v13 * rhs.v32;
            this->v13 = this->v10 * rhs.v03 + this->v11 * rhs.v13 + this->v12 * rhs.v23 + this->v13 * rhs.v33;

            this->v20 = this->v20 * rhs.v00 + this->v21 * rhs.v10 + this->v22 * rhs.v20 + this->v23 * rhs.v30;
            this->v21 = this->v20 * rhs.v01 + this->v21 * rhs.v11 + this->v22 * rhs.v21 + this->v23 * rhs.v31;
            this->v22 = this->v20 * rhs.v02 + this->v21 * rhs.v12 + this->v22 * rhs.v22 + this->v23 * rhs.v32;
            this->v23 = this->v20 * rhs.v03 + this->v21 * rhs.v13 + this->v22 * rhs.v23 + this->v23 * rhs.v33;

            this->v30 = this->v30 * rhs.v00 + this->v31 * rhs.v10 + this->v32 * rhs.v20 + this->v33 * rhs.v30;
            this->v31 = this->v30 * rhs.v01 + this->v31 * rhs.v11 + this->v32 * rhs.v21 + this->v33 * rhs.v31;
            this->v32 = this->v30 * rhs.v02 + this->v31 * rhs.v12 + this->v32 * rhs.v22 + this->v33 * rhs.v32;
            this->v33 = this->v30 * rhs.v03 + this->v31 * rhs.v13 + this->v32 * rhs.v23 + this->v33 * rhs.v33;

            return *this;
        }

        inline float& operator[](size_t idx)
        {
            return this->data[idx];
        }

        inline const float& operator[](size_t idx) const
        {
            return this->data[idx];
        }
    };
}