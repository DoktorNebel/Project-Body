#include "Text.h"

#include "MathFunctions.h"
#include "Font.h"

namespace se
{
    Text::Text(Font* font, std::string text, se::Vector2 position, se::Vector2 size, float rotation, se::Vector4 color)
        : font(font)
        , text(text)
        , position(position)
        , size(size)
        , rotation(rotation)
        , color(color)
    {
        this->recalculate();
    }


    void Text::recalculate()
    {
        this->glyphs.clear();
        this->matrices.clear();
        this->textureRects.clear();

        std::string::iterator iter = this->text.begin();

        this->width = 0;

        while (iter != this->text.end())
        {
            this->glyphs.push_back(this->font->getGlyph(*iter));
            this->width += this->glyphs.back().width;

            ++iter;
        }

        se::Vector2 origin = this->position - se::Vector2((float)this->width / 2 * this->size.x, -(float)this->font->getHeight() / 2 * this->size.y);
        int xOffset = 0;

        for (unsigned int i = 0; i < this->glyphs.size(); ++i)
        {
            float kerning = 0.0f;
            if (i + 1 < this->glyphs.size())
            {
                unsigned int pos = std::find(this->glyphs[i].kerningChars.begin(), this->glyphs[i].kerningChars.end(), this->glyphs[i + 1].character) - this->glyphs[i].kerningChars.begin();
                if (pos < this->glyphs[i].kerningChars.size())
                    kerning = (float)this->glyphs[i].kerningAdvances[pos];
            }

            Matrix translation = Math::TranslationMatrix(origin.x + xOffset + this->glyphs[i].offset.x * this->size.x + kerning * this->size.x, origin.y + this->glyphs[i].offset.y * this->size.y, this->depth);
            Matrix rotation = Math::RotationMatrixZ(this->rotation);
            Matrix scale = Math::ScalingMatrix(this->size.x * this->width, this->size.y * this->font->getHeight(), 1.0f);

            this->matrices.push_back(translation * rotation * scale);
            this->textureRects.push_back(this->glyphs[i].textureRect);

            xOffset += this->glyphs[i].width * (int)this->size.x;
        }
    }


    Font* Text::getFont()
    {
        return this->font;
    }


    std::vector<Matrix>& Text::getMatrices()
    {
        return this->matrices;
    }


    void Text::move(Vector2 translation)
    {
        this->position += translation;
    }


    Vector2 Text::getPosition()
    {
        return this->position;
    }


    std::vector<Rectangle>& Text::getTextureRects()
    {
        return this->textureRects;
    }


    Rectangle Text::getRect()
    {
        Vector2 newVerts[4];

        float radRot = this->rotation * 0.0174532925f;

        Vector2 pos = this->position + Vector2(this->width / 2 * -this->size.x, this->font->getHeight() / 2 * -this->size.y);
        newVerts[0] = Vector2(this->position.x + (pos.x - this->position.x) * cos(radRot) - this->position.y + (pos.y - this->position.y) * sin(radRot),
            this->position.x + (pos.x - this->position.x) * sin(radRot) + this->position.y + (pos.y - this->position.y) * cos(radRot));

        pos = this->position + Vector2(this->width / 2 * -this->size.x, this->font->getHeight() / 2 * this->size.y);
        newVerts[1] = Vector2(this->position.x + (pos.x - this->position.x) * cos(radRot) - this->position.y + (pos.y - this->position.y) * sin(radRot),
            this->position.x + (pos.x - this->position.x) * sin(radRot) + this->position.y + (pos.y - this->position.y) * cos(radRot));

        pos = this->position + Vector2(this->width / 2 * this->size.x, this->font->getHeight() / 2 * this->size.y);
        newVerts[2] = Vector2(this->position.x + (pos.x - this->position.x) * cos(radRot) - this->position.y + (pos.y - this->position.y) * sin(radRot),
            this->position.x + (pos.x - this->position.x) * sin(radRot) + this->position.y + (pos.y - this->position.y) * cos(radRot));

        pos = this->position + Vector2(this->width / 2 * this->size.x, this->font->getHeight() / 2 * -this->size.y);
        newVerts[3] = Vector2(this->position.x + (pos.x - this->position.x) * cos(radRot) - this->position.y + (pos.y - this->position.y) * sin(radRot),
            this->position.x + (pos.x - this->position.x) * sin(radRot) + this->position.y + (pos.y - this->position.y) * cos(radRot));

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


    void Text::setPosition(Vector2 position)
    {
        this->position = position;
    }


    void Text::scale(Vector2 factor)
    {
        this->size *= factor;
    }


    Vector2 Text::getScale()
    {
        return this->size;
    }


    unsigned int Text::getWidth()
    {
        return this->width;
    }


    unsigned int Text::getHeight()
    {
        return this->font->getHeight();
    }


    void Text::setScale(Vector2 scale)
    {
        this->size = scale;
    }


    void Text::rotate(float rotation)
    {
        this->rotation += rotation;
    }


    float Text::getRotation()
    {
        return this->rotation;
    }


    void Text::setRotation(float rotation)
    {
        this->rotation = rotation;
    }


    void Text::setDepth(float depth)
    {
        this->depth = depth;
    }


    Vector4 Text::getColor()
    {
        return this->color;
    }


    void Text::setColor(Vector4 color)
    {
        this->color = color;
    }


    void Text::setText(std::string text)
    {
        this->text = text;
        this->recalculate();
    }
}