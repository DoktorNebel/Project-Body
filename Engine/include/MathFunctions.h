#pragma once

#include "Matrix.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


namespace se
{
    bool operator==(const Vector2& lhs, const Vector2& rhs);
    Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
    Vector2 operator*(const Vector2& lhs, const Vector2& rhs);
    Vector2 operator/(const Vector2& lhs, const Vector2& rhs);

    Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
    Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
    Vector3 operator/(const Vector3& lhs, const Vector3& rhs);

    Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
    Vector4 operator*(const Vector4& lhs, const Vector4& rhs);
    Vector4 operator/(const Vector4& lhs, const Vector4& rhs);

    Matrix operator+(const Matrix& lhs, const Matrix& rhs);
    Matrix operator-(const Matrix& lhs, const Matrix& rhs);
    Matrix operator*(const Matrix& lhs, const Matrix& rhs);
    Matrix operator*(const float lhs, const Matrix& rhs);

	Vector2 operator*(const Vector2& lhs, const float rhs);
	Vector2 operator/(const Vector2& lhs, const float rhs);

    Vector3 operator*(const Vector3& lhs, const float rhs);
    Vector3 operator/(const Vector3& lhs, const float rhs);

    Vector4 operator*(const Vector4& lhs, const float rhs);
    Vector4 operator/(const Vector4& lhs, const float rhs);
    Vector4 operator*(const Matrix& lhs, const Vector4& rhs);


    namespace Math
    {
        float Clamp(float min, float max, float value);
        float Lerp(float min, float max, float lerpValue);

        float Length(const Vector2& vector);
        float Length(const Vector3& vector);
        Vector2 Perpendicular(const Vector2& vector);
        Vector3 Cross(const Vector3& first, const Vector3& second);
        float Dot(const Vector2& first, const Vector2& second);
		float Dot(const Vector3& first, const Vector3& second);
		Vector2& Normalize(Vector2& vector);
		Vector2 GetNormalized(const Vector2& vector);
        Vector3& Normalize(Vector3& vector);
        Vector3 GetNormalized(const Vector3& vector);
        float Angle(const Vector3& first, const Vector3& second);
        float Distance(const Vector2& first, const Vector2& second);

        Matrix IdentityMatrix();
        Matrix TranslationMatrix(float x, float y, float z);
        Matrix ScalingMatrix(float x, float y, float z);
        Matrix RotationMatrixX(float angle);
        Matrix RotationMatrixY(float angle);
        Matrix RotationMatrixZ(float angle);
        Matrix RotationMatrixFromEuler(float roll, float pitch, float yaw);
        Matrix RotationMatrixLookAt(const Vector3& position, const Vector3& target);
        Matrix PerspectiveMatrix(float fov, float aspectRatio, float nearZ, float farZ);
        Matrix OrthographicMatrix(float width, float height, float nearZ, float farZ);
        Matrix& Transpose(Matrix& matrix);
        Matrix GetTransposed(const Matrix& matrix);
        float Determinant(const Matrix& matrix);
        Matrix& Invert(Matrix& matrix);
        Matrix GetInverse(const Matrix& matrix);
    };
}