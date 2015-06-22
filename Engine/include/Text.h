#pragma once

#include <string>
#include <vector>
#include "Glyph.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Matrix.h"

namespace se
{
    class Font;


    class Text
    {
    private:

        Font* font;
        se::Vector2 position;
        se::Vector2 size;
        float rotation;
        se::Vector4 color;
        std::string text;
        float depth;
        unsigned int width;
        std::vector<Glyph> glyphs;
        std::vector<Matrix> matrices;
        std::vector<Rectangle> textureRects;

    public:

        Text(Font* font, std::string text = std::string(), se::Vector2 position = se::Vector2(0.0f, 0.0f), se::Vector2 size = se::Vector2(1.0f, 1.0f), float rotation = 0.0f, se::Vector4 color = se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));

    private:

        void recalculate();

    public:

        Font* getFont();
        std::vector<Matrix>& getMatrices();
        void move(Vector2 translation);
        Vector2 getPosition();
        std::vector<Rectangle>& getTextureRects();
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
        Vector4 getColor();
        void setColor(Vector4 color);
        void setText(std::string text);
    };
}