#include "Sprite.h"

#include "MathFunctions.h"
#include <cmath>

namespace se
{
    Sprite::Sprite()
        : texture(0)
        , textureRect(0, 0, 0, 0)
        , position(0, 0)
        , size(1, 1)
        , width(0)
        , height(0)
        , rotation(0.0f)
        , depth(0.0f)
    {

    }


    Sprite::Sprite(unsigned int texture, Rectangle textureRect, Vector2 position, float width, float height)
        : texture(texture)
        , textureRect(textureRect)
        , position(position)
        , size(1, 1)
        , width(width)
        , height(height)
        , rotation(0.0f)
        , depth(0.0f)
    {
    }


    Sprite::~Sprite()
    {
    }


    unsigned int Sprite::getTextureId()
    {
        return this->texture;
    }


    Matrix Sprite::getMatrix()
    {
        Matrix translation = Math::TranslationMatrix(this->position.x, this->position.y, this->depth);
        Matrix rotation = Math::RotationMatrixZ(this->rotation);
        Matrix scale = Math::ScalingMatrix(this->size.x * this->width, this->size.y * this->height, 1.0f);

        return translation * rotation * scale;
    }


    void Sprite::move(Vector2 translation)
    {
        this->position += translation;
    }


    Vector2 Sprite::getPosition()
    {
        return this->position;
    }


    Rectangle Sprite::getTextureRect()
    {
        return this->textureRect;
    }


    Rectangle Sprite::getRect()
    {
        Vector2 newVerts[4];

        Vector2 pos = this->position + Vector2(-this->width / 2 * this->size.x, -this->height / 2 * this->size.y);
        newVerts[0] = Vector2(pos.x * cos(this->rotation) - pos.y * sin(this->rotation), pos.x * sin(this->rotation) + pos.y * cos(this->rotation));

        pos = this->position + Vector2(-this->width / 2 * this->size.x, this->height / 2 * this->size.y);
        newVerts[1] = Vector2(pos.x * cos(this->rotation) - pos.y * sin(this->rotation), pos.x * sin(this->rotation) + pos.y * cos(this->rotation));

        pos = this->position + Vector2(this->width / 2 * this->size.x, this->height / 2 * this->size.y);
        newVerts[2] = Vector2(pos.x * cos(this->rotation) - pos.y * sin(this->rotation), pos.x * sin(this->rotation) + pos.y * cos(this->rotation));

        pos = this->position + Vector2(this->width / 2 * this->size.x, -this->height / 2 * this->size.y);
        newVerts[3] = Vector2(pos.x * cos(this->rotation) - pos.y * sin(this->rotation), pos.x * sin(this->rotation) + pos.y * cos(this->rotation));

        float minX = newVerts[0].x;
        float maxX = newVerts[0].x;
        float minY = newVerts[0].y;
        float maxY = newVerts[0].y;

        for (int i = 1; i < 4; ++i)
        {
            minX = newVerts[i].x < minX ? newVerts[i].x : minX;
            maxX = newVerts[i].x > maxX ? newVerts[i].x : maxX;
            minY = newVerts[i].y < minY ? newVerts[i].y : minY;
            maxY = newVerts[i].y > maxY ? newVerts[i].y : maxY;
        }

        return Rectangle(minY, maxY, minX, maxX);
    }


    void Sprite::setPosition(Vector2 position)
    {
        this->position = position;
    }


    void Sprite::scale(Vector2 factor)
    {
        this->size *= factor;
    }


    Vector2 Sprite::getScale()
    {
        return this->size;
    }


    float Sprite::getWidth()
    {
        return this->width;
    }


    float Sprite::getHeight()
    {
        return this->height;
    }


    void Sprite::setScale(Vector2 scale)
    {
        this->size = scale;
    }


    void Sprite::rotate(float rotation)
    {
        this->rotation += rotation;
    }


    float Sprite::getRotation()
    {
        return this->rotation;
    }


    void Sprite::setRotation(float rotation)
    {
        this->rotation = rotation;
    }


    void Sprite::setDepth(float depth)
    {
        this->depth = depth;
    }
}