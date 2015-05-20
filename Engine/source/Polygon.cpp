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


    bool Polygon::overlap(Polygon& other)
    {
        return false;
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
            //this->points[i] = Vector2(this->position.x + (this->points[i].x - this->position.x) * c - this->position.y + (this->points[i].y - this->position.y) * s,
            //    this->position.x + (this->points[i].x - this->position.x) * s + this->position.y + (this->points[i].y - this->position.y) * c);
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