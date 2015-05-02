#pragma once

#include "Vector2.h"
#include "Rectangle.h"
#include "Matrix.h"

namespace se
{
    class Sprite
    {
    private:

        unsigned int texture;
        Rectangle textureRect;
        Vector2 position;
        Vector2 size;
        float width;
        float height;
        float rotation;
        float depth;

    public:

        Sprite();
        Sprite(unsigned int texture, Rectangle textureRect, Vector2 position, float width, float height);
        ~Sprite();

    public:

        unsigned int getTextureId();
        Matrix getMatrix();
        void move(Vector2 translation);
        Vector2 getPosition();
        Rectangle getTextureRect();
        Rectangle getRect();
        void setPosition(Vector2 position);
        void scale(Vector2 factor);
        Vector2 getScale();
        float getWidth();
        float getHeight();
        void setScale(Vector2 scale);
        void rotate(float rotation);
        float getRotation();
        void setRotation(float rotation);
        void setDepth(float depth);
    };
}
