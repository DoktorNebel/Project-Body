#include "Polygon.h"

#include "MathFunctions.h"

namespace se
{
    Polygon::Polygon()
        : position(Vector2(0.0f, 0.0f))
        , rotation(0.0f)
        , size(Vector2(1.0f, 1.0f))
    {

    }


    Polygon::Polygon(std::vector<se::Vector2> points)
        : points(points)
        , position(Vector2(0.0f, 0.0f))
        , rotation(0.0f)
        , size(Vector2(1.0f, 1.0f))
    {

    }


    Polygon::~Polygon()
    {

    }


    bool Polygon::overlap(const Polygon& other, Vector2* projectionNormal, float* projectionScalar)
    {
        std::vector<Vector2> axes;
        for (int i = 0; i < this->points.size(); ++i)
        {
            axes.push_back(Math::GetNormalized(Math::Perpendicular(this->points[(i + 1) % this->points.size()] - this->points[i])));
        }

        for (int i = 0; i < other.points.size(); ++i)
        {
            axes.push_back(Math::GetNormalized(Math::Perpendicular(other.points[(i + 1) % other.points.size()] - other.points[i])));
        }

        int minAxis = -1;
        float minLength = 1000000.0f;

        for (int i = 0; i < axes.size(); ++i)
        {
            float firstMin;
            float firstMax = firstMin = Math::Dot(this->points[0], axes[i]);
            for (int j = 1; j < this->points.size(); ++j)
            {
                float value = Math::Dot(this->points[j], axes[i]);
                if (value < firstMin)
                    firstMin = value;
                else if (value > firstMax)
                    firstMax = value;
            }

            float secondMin;
            float secondMax = secondMin = Math::Dot(other.points[0], axes[i]);
            for (int j = 1; j < other.points.size(); ++j)
            {
                float value = Math::Dot(other.points[j], axes[i]);
                if (value < secondMin)
                    secondMin = value;
                else if (value > secondMax)
                    secondMax = value;
            }

            if (firstMin > secondMax || firstMax < secondMin)
            {
                return false;
            }
            else
            {
                float length;
                if ((length = Math::Length(axes[i] * (firstMin - secondMax))) < minLength)
                {
                    minLength = length;
                    minAxis = i;
                }
                if ((length = Math::Length(axes[i] * (firstMax - secondMin))) < minLength)
                {
                    minLength = length;
                    minAxis = i;
                }
            }
        }

        *projectionNormal = axes[minAxis];
        *projectionScalar = minLength;

        return true;
    }


    const std::vector<Vector2>& Polygon::getPoints()
    {
        return this->points;
    }


    void Polygon::setPosition(Vector2 position)
    {
        this->move(position - this->position);
    }


    void Polygon::move(Vector2 movement)
    {
        this->position += movement;
        for (int i = 0; i < this->points.size(); ++i)
        {
            this->points[i] += movement;
        }
    }


    void Polygon::setRotation(float rotation)
    {
        this->rotate(rotation - this->rotation);
    }


    void Polygon::rotate(float rotation)
    {
        this->rotation += rotation;
        float radRot = rotation * 0.0174532925f;
        float s = sin(radRot);
        float c = cos(radRot);
        for (int i = 0; i < this->points.size(); ++i)
        {
            this->points[i] -= this->position;

            float newX = this->points[i].x * c - this->points[i].y * s;
            float newY = this->points[i].x * s + this->points[i].y * c;

            this->points[i] = Vector2(newX, newY) + this->position;
        }
    }


    void Polygon::setScale(Vector2 scale)
    {
        this->scale(scale / this->size);
    }


    void Polygon::scale(Vector2 factor)
    {
        float rot = this->rotation;
        this->setRotation(0);
        this->size *= factor;
        for (int i = 0; i < this->points.size(); ++i)
        {
            this->points[i] -= this->position;

            float newX = this->points[i].x * factor.x;
            float newY = this->points[i].y * factor.y;

            this->points[i] = Vector2(newX, newY) + this->position;
        }
        this->setRotation(rot);
    }
}