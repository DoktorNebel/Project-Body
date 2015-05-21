#include "MathFunctions.h"

#include <string.h>
#include <cmath>


namespace se
{
    //Vector3 operators

    Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
    {
        return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
    }


    Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
    {
        return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
    }


    Vector2 operator*(const Vector2& lhs, const Vector2& rhs)
    {
        return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
    }


    Vector2 operator/(const Vector2& lhs, const Vector2& rhs)
    {
        return Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
    }



    //Vector3 operators

    Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs.x + rhs.x,
            lhs.y + rhs.y,
            lhs.z + rhs.z);
    }


    Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs.x - rhs.x,
            lhs.y - rhs.y,
            lhs.z - rhs.z);
    }


    Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs.x * rhs.x,
            lhs.y * rhs.y,
            lhs.z * rhs.z);
    }


    Vector3 operator/(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs.x / rhs.x,
            lhs.y / rhs.y,
            lhs.z / rhs.z);
    }


    //Vector4 operators

    Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(lhs.x + rhs.x,
            lhs.y + rhs.y,
            lhs.z + rhs.z,
            lhs.w + rhs.w);
    }


    Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(lhs.x - rhs.x,
            lhs.y - rhs.y,
            lhs.z - rhs.z,
            lhs.w - rhs.w);
    }


    Vector4 operator*(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(lhs.x * rhs.x,
            lhs.y * rhs.y,
            lhs.z * rhs.z,
            lhs.w * rhs.w);
    }


    Vector4 operator/(const Vector4& lhs, const Vector4& rhs)
    {
        return Vector4(lhs.x / rhs.x,
            lhs.y / rhs.y,
            lhs.z / rhs.z,
            lhs.w / rhs.w);
    }


    //Matrix operators

    Matrix operator+(const Matrix& lhs, const Matrix& rhs)
    {
        Matrix result;

        for (int i = 0; i < 16; ++i)
        {
            result[i] = lhs[i] + rhs[i];
        }

        return result;
    }


    Matrix operator-(const Matrix& lhs, const Matrix& rhs)
    {
        Matrix result;

        for (int i = 0; i < 16; ++i)
        {
            result[i] = lhs[i] - rhs[i];
        }

        return result;
    }


    Matrix operator*(const Matrix& lhs, const Matrix& rhs)
    {
        Matrix result;

        result.v00 = lhs.v00 * rhs.v00 + lhs.v01 * rhs.v10 + lhs.v02 * rhs.v20 + lhs.v03 * rhs.v30;
        result.v01 = lhs.v00 * rhs.v01 + lhs.v01 * rhs.v11 + lhs.v02 * rhs.v21 + lhs.v03 * rhs.v31;
        result.v02 = lhs.v00 * rhs.v02 + lhs.v01 * rhs.v12 + lhs.v02 * rhs.v22 + lhs.v03 * rhs.v32;
        result.v03 = lhs.v00 * rhs.v03 + lhs.v01 * rhs.v13 + lhs.v02 * rhs.v23 + lhs.v03 * rhs.v33;

        result.v10 = lhs.v10 * rhs.v00 + lhs.v11 * rhs.v10 + lhs.v12 * rhs.v20 + lhs.v13 * rhs.v30;
        result.v11 = lhs.v10 * rhs.v01 + lhs.v11 * rhs.v11 + lhs.v12 * rhs.v21 + lhs.v13 * rhs.v31;
        result.v12 = lhs.v10 * rhs.v02 + lhs.v11 * rhs.v12 + lhs.v12 * rhs.v22 + lhs.v13 * rhs.v32;
        result.v13 = lhs.v10 * rhs.v03 + lhs.v11 * rhs.v13 + lhs.v12 * rhs.v23 + lhs.v13 * rhs.v33;

        result.v20 = lhs.v20 * rhs.v00 + lhs.v21 * rhs.v10 + lhs.v22 * rhs.v20 + lhs.v23 * rhs.v30;
        result.v21 = lhs.v20 * rhs.v01 + lhs.v21 * rhs.v11 + lhs.v22 * rhs.v21 + lhs.v23 * rhs.v31;
        result.v22 = lhs.v20 * rhs.v02 + lhs.v21 * rhs.v12 + lhs.v22 * rhs.v22 + lhs.v23 * rhs.v32;
        result.v23 = lhs.v20 * rhs.v03 + lhs.v21 * rhs.v13 + lhs.v22 * rhs.v23 + lhs.v23 * rhs.v33;

        result.v30 = lhs.v30 * rhs.v00 + lhs.v31 * rhs.v10 + lhs.v32 * rhs.v20 + lhs.v33 * rhs.v30;
        result.v31 = lhs.v30 * rhs.v01 + lhs.v31 * rhs.v11 + lhs.v32 * rhs.v21 + lhs.v33 * rhs.v31;
        result.v32 = lhs.v30 * rhs.v02 + lhs.v31 * rhs.v12 + lhs.v32 * rhs.v22 + lhs.v33 * rhs.v32;
        result.v33 = lhs.v30 * rhs.v03 + lhs.v31 * rhs.v13 + lhs.v32 * rhs.v23 + lhs.v33 * rhs.v33;

        return result;
    }


    Matrix operator*(const float lhs, const Matrix& rhs)
    {
        Matrix result;

        for (int i = 0; i < 16; ++i)
        {
            result[i] = lhs * rhs[i];
        }

        return result;
    }


    //Mixed operators

	Vector2 operator*(const Vector2& lhs, const float rhs)
	{
		return Vector2(lhs.x * rhs, lhs.y * rhs);
	}


	Vector2 operator/(const Vector2& lhs, const float rhs)
	{
		return Vector2(lhs.x / rhs, lhs.y / rhs);
	}


    Vector3 operator*(const Vector3& lhs, const float rhs)
    {
        return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }


    Vector3 operator/(const Vector3& lhs, const float rhs)
    {
        return Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
    }


    Vector4 operator*(const Vector4& lhs, const float rhs)
    {
        return Vector4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
    }


    Vector4 operator/(const Vector4& lhs, const float rhs)
    {
        return Vector4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
    }


    Vector4 operator*(const Matrix& lhs, const Vector4& rhs)
    {
        return Vector4(lhs.v00 * rhs.x + lhs.v01 * rhs.y + lhs.v02 * rhs.z + lhs.v03 * rhs.w,
            lhs.v10 * rhs.x + lhs.v11 * rhs.y + lhs.v12 * rhs.z + lhs.v13 * rhs.w,
            lhs.v20 * rhs.x + lhs.v21 * rhs.y + lhs.v22 * rhs.z + lhs.v23 * rhs.w,
            lhs.v30 * rhs.x + lhs.v31 * rhs.y + lhs.v32 * rhs.z + lhs.v33 * rhs.w);
    }


    namespace Math
    {
        //
        //Miscellaneous functions
        //
        float Lerp(float min, float max, float lerpValue)
        {
            return min + (max - min) * lerpValue;
        }


        //
        //Vector functions
        //
        float Length(const Vector2& vector)
        {
            return sqrt(vector.x * vector.x + vector.y * vector.y);
        }


        float Length(const Vector3& vector)
        {
            return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
        }


        Vector2 Perpendicular(const Vector2& vector)
        {
            return Vector2(-vector.y, vector.x);
        }


        Vector3 Cross(const Vector3& first, const Vector3& second)
        {
            return Vector3(first.y * second.z - first.z * second.y,
                first.z * second.x - first.x * second.z,
                first.x * second.y - first.y * second.x);
        }


        float Dot(const Vector2& first, const Vector2& second)
        {
            return first.x * second.x + first.y * second.y;
        }


        float Dot(const Vector3& first, const Vector3& second)
        {
            return first.x * second.x + first.y * second.y + first.z * second.z;
        }


		Vector2& Normalize(Vector2& vector)
		{
			vector /= Math::Length(vector);

			return vector;
		}


		Vector2 GetNormalized(const Vector2& vector)
		{
			float length = Math::Length(vector);

			return Vector2(vector.x / length,
				vector.y / length);
		}


        Vector3& Normalize(Vector3& vector)
        {
            vector /= Math::Length(vector);

            return vector;
        }


        Vector3 GetNormalized(const Vector3& vector)
        {
            float length = Math::Length(vector);

            return Vector3(vector.x / length,
                vector.y / length,
                vector.z / length);
        }


        float Angle(const Vector3& first, const Vector3& second)
        {
            return acos(Math::Dot(first, second) / (Math::Length(first) * Math::Length(second)));
        }


        float Distance(const Vector2& first, const Vector2& second)
        {
            float value = Math::Length(second - first);
            return value < 0 ? -value : value;
        }


        //
        //Matrix functions
        //
        Matrix IdentityMatrix()
        {
            Matrix result;

            memset(&result, 0, sizeof(Matrix));

            result.v00 = 1;
            result.v11 = 1;
            result.v22 = 1;
            result.v33 = 1;

            return result;
        }


        Matrix TranslationMatrix(float x, float y, float z)
        {
            Matrix result = Math::IdentityMatrix();

            result.v03 = x;
            result.v13 = y;
            result.v23 = z;

            return result;
        }


        Matrix ScalingMatrix(float x, float y, float z)
        {
            Matrix result;

            memset(&result, 0, sizeof(Matrix));

            result.v00 = x;
            result.v11 = y;
            result.v22 = z;
            result.v33 = 1;

            return result;
        }


        Matrix RotationMatrixX(float angle)
        {
            angle *= 0.0174532925;

            Matrix result = Math::IdentityMatrix();

            result.v11 = cos(angle);
            result.v12 = -sin(angle);

            result.v21 = sin(angle);
            result.v22 = cos(angle);

            return result;
        }


        Matrix RotationMatrixY(float angle)
        {
            angle *= 0.0174532925;

            Matrix result = Math::IdentityMatrix();

            result.v00 = cos(angle);
            result.v02 = sin(angle);

            result.v20 = -sin(angle);
            result.v22 = cos(angle);

            return result;
        }


        Matrix RotationMatrixZ(float angle)
        {
            angle *= 0.0174532925;

            Matrix result = Math::IdentityMatrix();

            result.v00 = cos(angle);
            result.v01 = -sin(angle);

            result.v10 = sin(angle);
            result.v11 = cos(angle);

            return result;
        }


        Matrix RotationMatrixFromEuler(float roll, float pitch, float yaw)
        {
            roll *= 0.0174532925;
            pitch *= 0.0174532925;
            yaw *= 0.0174532925;

            Matrix result;

            result.v00 = cos(yaw) * cos(pitch);
            result.v01 = cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll);
            result.v02 = cos(yaw) * sin(pitch) * cos(roll) + sin(yaw) * sin(roll);
            result.v03 = 0;

            result.v10 = sin(yaw) * cos(pitch);
            result.v11 = sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll);
            result.v12 = sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll);
            result.v13 = 0;

            result.v20 = -sin(pitch);
            result.v21 = cos(pitch) * sin(roll);
            result.v22 = cos(pitch) * cos(roll);
            result.v23 = 0;

            result.v30 = 0;
            result.v31 = 0;
            result.v32 = 0;
            result.v33 = 1;

            return result;
        }


        Matrix RotationMatrixLookAt(const Vector3& position, const Vector3& target)
        {
            Vector3 up(0, 1, 0);
            Vector3 forward = Math::Normalize(position - target);
            Vector3 right = Math::Normalize(Math::Cross(up, forward));
            up = Math::Cross(forward, right);

            Matrix result = Math::IdentityMatrix();

            result.v00 = right.x;
            result.v01 = right.y;
            result.v02 = right.z;

            result.v10 = up.x;
            result.v11 = up.y;
            result.v12 = up.z;

            result.v20 = forward.x;
            result.v21 = forward.y;
            result.v22 = forward.z;

            result.v03 = -Math::Dot(right, position);
            result.v13 = -Math::Dot(up, position);
            result.v23 = -Math::Dot(forward, position);

            return result;
        }


        Matrix PerspectiveMatrix(float fov, float aspectRatio, float nearZ, float farZ)
        {
            float f = 1 / tan((fov / 2) * 0.0174532925);

            Matrix result = Math::IdentityMatrix();

            result.v00 = f / aspectRatio;
            result.v11 = f;
            result.v22 = (farZ + nearZ) / (nearZ - farZ);
            result.v23 = (2 * farZ * nearZ) / (nearZ - farZ);
            result.v32 = -1;
            result.v33 = 0;

            return result;
        }


        Matrix OrthographicMatrix(float width, float height, float nearZ, float farZ)
        {
            Matrix result = Math::IdentityMatrix();

            result.v00 = 2.0f / width;
            result.v11 = 2.0f / height;
            result.v22 = 1 / (farZ - nearZ);
            result.v23 = -nearZ / (farZ - nearZ);

            return result;
        }


        Matrix& Transpose(Matrix& matrix)
        {
            matrix = GetTransposed(matrix);

            return matrix;
        }


        Matrix GetTransposed(const Matrix& matrix)
        {
            Matrix result;

            result.v00 = matrix.v00;
            result.v01 = matrix.v10;
            result.v02 = matrix.v20;
            result.v03 = matrix.v30;

            result.v10 = matrix.v01;
            result.v11 = matrix.v11;
            result.v12 = matrix.v21;
            result.v13 = matrix.v31;

            result.v20 = matrix.v02;
            result.v21 = matrix.v12;
            result.v22 = matrix.v22;
            result.v23 = matrix.v32;

            result.v30 = matrix.v03;
            result.v31 = matrix.v13;
            result.v32 = matrix.v23;
            result.v33 = matrix.v33;

            return result;
        }


        float Determinant(const Matrix& matrix)
        {
            return matrix.v00 * matrix.v11 * matrix.v22 * matrix.v33 + matrix.v00 * matrix.v12 * matrix.v23 * matrix.v31 + matrix.v00 * matrix.v13 * matrix.v21 * matrix.v32
                + matrix.v01 * matrix.v10 * matrix.v23 * matrix.v32 + matrix.v01 * matrix.v12 * matrix.v20 * matrix.v33 + matrix.v01 * matrix.v13 * matrix.v22 * matrix.v30
                + matrix.v02 * matrix.v10 * matrix.v21 * matrix.v33 + matrix.v02 * matrix.v11 * matrix.v23 * matrix.v30 + matrix.v02 * matrix.v13 * matrix.v20 * matrix.v31
                + matrix.v03 * matrix.v10 * matrix.v22 * matrix.v31 + matrix.v03 * matrix.v11 * matrix.v20 * matrix.v32 + matrix.v03 * matrix.v12 * matrix.v21 * matrix.v30
                - matrix.v00 * matrix.v11 * matrix.v23 * matrix.v32 - matrix.v00 * matrix.v12 * matrix.v21 * matrix.v33 - matrix.v00 * matrix.v13 * matrix.v22 * matrix.v31
                - matrix.v01 * matrix.v10 * matrix.v22 * matrix.v33 - matrix.v01 * matrix.v12 * matrix.v23 * matrix.v30 - matrix.v01 * matrix.v13 * matrix.v20 * matrix.v32
                - matrix.v02 * matrix.v10 * matrix.v23 * matrix.v31 - matrix.v02 * matrix.v11 * matrix.v20 * matrix.v33 - matrix.v02 * matrix.v13 * matrix.v21 * matrix.v30
                - matrix.v03 * matrix.v10 * matrix.v21 * matrix.v32 - matrix.v03 * matrix.v11 * matrix.v22 * matrix.v30 - matrix.v03 * matrix.v12 * matrix.v20 * matrix.v31;
        }


        Matrix& Invert(Matrix& matrix)
        {
            matrix = Math::GetInverse(matrix);

            return matrix;
        }


        Matrix GetInverse(const Matrix& matrix)
        {
            Matrix result;

            result.v00 = matrix.v11 * matrix.v22 * matrix.v33 + matrix.v12 * matrix.v23 * matrix.v31 + matrix.v13 * matrix.v21 * matrix.v32 - matrix.v11 * matrix.v23 * matrix.v32 - matrix.v12 * matrix.v21 * matrix.v33 - matrix.v13 * matrix.v22 * matrix.v31;
            result.v01 = matrix.v01 * matrix.v23 * matrix.v32 + matrix.v02 * matrix.v21 * matrix.v33 + matrix.v03 * matrix.v22 * matrix.v31 - matrix.v01 * matrix.v22 * matrix.v33 - matrix.v02 * matrix.v23 * matrix.v31 - matrix.v03 * matrix.v21 * matrix.v32;
            result.v02 = matrix.v01 * matrix.v12 * matrix.v33 + matrix.v02 * matrix.v13 * matrix.v31 + matrix.v03 * matrix.v11 * matrix.v32 - matrix.v01 * matrix.v13 * matrix.v32 - matrix.v02 * matrix.v11 * matrix.v33 - matrix.v03 * matrix.v12 * matrix.v31;
            result.v03 = matrix.v01 * matrix.v13 * matrix.v22 + matrix.v02 * matrix.v11 * matrix.v23 + matrix.v03 * matrix.v12 * matrix.v21 - matrix.v01 * matrix.v12 * matrix.v23 - matrix.v02 * matrix.v13 * matrix.v21 - matrix.v03 * matrix.v11 * matrix.v22;

            result.v10 = matrix.v10 * matrix.v23 * matrix.v32 + matrix.v12 * matrix.v20 * matrix.v33 + matrix.v13 * matrix.v22 * matrix.v30 - matrix.v10 * matrix.v22 * matrix.v33 - matrix.v10 * matrix.v23 * matrix.v30 - matrix.v13 * matrix.v20 * matrix.v32;
            result.v11 = matrix.v00 * matrix.v22 * matrix.v33 + matrix.v02 * matrix.v23 * matrix.v30 + matrix.v03 * matrix.v20 * matrix.v32 - matrix.v00 * matrix.v23 * matrix.v32 - matrix.v02 * matrix.v20 * matrix.v33 - matrix.v03 * matrix.v22 * matrix.v30;
            result.v12 = matrix.v00 * matrix.v13 * matrix.v32 + matrix.v02 * matrix.v10 * matrix.v33 + matrix.v03 * matrix.v12 * matrix.v30 - matrix.v00 * matrix.v12 * matrix.v33 - matrix.v02 * matrix.v13 * matrix.v30 - matrix.v03 * matrix.v10 * matrix.v32;
            result.v13 = matrix.v00 * matrix.v12 * matrix.v23 + matrix.v02 * matrix.v13 * matrix.v20 + matrix.v03 * matrix.v10 * matrix.v22 - matrix.v00 * matrix.v13 * matrix.v22 - matrix.v02 * matrix.v10 * matrix.v23 - matrix.v03 * matrix.v12 * matrix.v20;

            result.v20 = matrix.v10 * matrix.v21 * matrix.v33 + matrix.v11 * matrix.v23 * matrix.v30 + matrix.v13 * matrix.v20 * matrix.v31 - matrix.v10 * matrix.v23 * matrix.v31 - matrix.v11 * matrix.v20 * matrix.v33 - matrix.v13 * matrix.v21 * matrix.v30;
            result.v21 = matrix.v00 * matrix.v23 * matrix.v31 + matrix.v01 * matrix.v20 * matrix.v33 + matrix.v03 * matrix.v21 * matrix.v30 - matrix.v00 * matrix.v21 * matrix.v33 - matrix.v01 * matrix.v23 * matrix.v30 - matrix.v03 * matrix.v20 * matrix.v31;
            result.v22 = matrix.v00 * matrix.v11 * matrix.v33 + matrix.v01 * matrix.v13 * matrix.v30 + matrix.v03 * matrix.v10 * matrix.v31 - matrix.v00 * matrix.v13 * matrix.v31 - matrix.v01 * matrix.v10 * matrix.v33 - matrix.v03 * matrix.v11 * matrix.v30;
            result.v23 = matrix.v00 * matrix.v13 * matrix.v21 + matrix.v01 * matrix.v10 * matrix.v23 + matrix.v03 * matrix.v11 * matrix.v20 - matrix.v00 * matrix.v11 * matrix.v23 - matrix.v01 * matrix.v13 * matrix.v20 - matrix.v03 * matrix.v10 * matrix.v21;

            result.v30 = matrix.v10 * matrix.v22 * matrix.v31 + matrix.v11 * matrix.v20 * matrix.v32 + matrix.v12 * matrix.v21 * matrix.v30 - matrix.v10 * matrix.v21 * matrix.v32 - matrix.v11 * matrix.v22 * matrix.v30 - matrix.v12 * matrix.v20 * matrix.v31;
            result.v31 = matrix.v00 * matrix.v21 * matrix.v32 + matrix.v01 * matrix.v22 * matrix.v30 + matrix.v02 * matrix.v20 * matrix.v31 - matrix.v00 * matrix.v22 * matrix.v31 - matrix.v01 * matrix.v20 * matrix.v32 - matrix.v02 * matrix.v21 * matrix.v30;
            result.v32 = matrix.v00 * matrix.v12 * matrix.v31 + matrix.v01 * matrix.v10 * matrix.v32 + matrix.v02 * matrix.v11 * matrix.v30 - matrix.v00 * matrix.v11 * matrix.v32 - matrix.v01 * matrix.v12 * matrix.v30 - matrix.v02 * matrix.v10 * matrix.v31;
            result.v33 = matrix.v00 * matrix.v11 * matrix.v22 + matrix.v01 * matrix.v12 * matrix.v20 + matrix.v02 * matrix.v10 * matrix.v21 - matrix.v00 * matrix.v12 * matrix.v21 - matrix.v01 * matrix.v10 * matrix.v22 - matrix.v02 * matrix.v11 * matrix.v20;

            return (1 / Math::Determinant(matrix)) * result;
        }
    }
}