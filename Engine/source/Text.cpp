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
        , depth(0.0f)
    {
        if (this->font)
        {
            this->getGlyphs();
            this->recalculate();
        }
    }


    void Text::getGlyphs()
    {
        this->glyphs.clear();

        std::string::iterator iter = this->text.begin();

        this->width = 0;

        while (iter != this->text.end())
        {
            this->glyphs.push_back(this->font->getGlyph(*iter));
            this->width += (unsigned int)((float)this->glyphs.back().advance * this->size.x);

            ++iter;
        }
    }


    void Text::recalculate()
    {
        this->matrices.clear();
        this->textureRects.clear();

        se::Vector2 origin = this->position -se::Vector2((float)this->width / 2.0f * this->size.x, (float)this->font->getHeight() / 2.0f * this->size.y);
        int xOffset = 0;

        for (unsigned int i = 0; i < this->glyphs.size(); ++i)
        {
            float kerning = 0.0f;
            if ((int)i - 1 >= 0)
            {
                unsigned int pos = std::find(this->glyphs[i - 1].kerningChars.begin(), this->glyphs[i - 1].kerningChars.end(), this->glyphs[i].character) - this->glyphs[i - 1].kerningChars.begin();
                if (pos < this->glyphs[i - 1].kerningChars.size())
                    kerning = (float)this->glyphs[i - 1].kerningAdvances[pos];
            }

            //Matrix translation = Math::TranslationMatrix(origin.x + xOffset + this->glyphs[i].offset.x * this->size.x + kerning * this->size.x + (float)this->glyphs[i].width / 2.0f, origin.y + this->glyphs[i].offset.y * this->size.y - (float)this->glyphs[i].height / 2.0f, this->depth);
            Matrix translation = Math::TranslationMatrix(this->position.x, this->position.y, this->depth);
            Matrix rotation = Math::RotationMatrixZ(this->rotation) * Math::TranslationMatrix(origin.x - this->position.x + xOffset + this->glyphs[i].offset.x * this->size.x + kerning * this->size.x + (float)this->glyphs[i].width / 2.0f, origin.y - this->position.y + this->glyphs[i].offset.y * this->size.y - (float)this->glyphs[i].height / 2.0f, 0.0f);
            Matrix scale = Math::ScalingMatrix(this->size.x * (float)this->glyphs[i].width, this->size.y * (float)this->glyphs[i].height, 1.0f);

            this->matrices.push_back(translation * rotation * scale);
            this->textureRects.push_back(this->glyphs[i].textureRect);

            xOffset += (int)(this->glyphs[i].advance * this->size.x);
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
        this->recalculate();
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
        this->recalculate();
    }


    void Text::scale(Vector2 factor)
    {
        this->size *= factor;
        this->recalculate();
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
        this->recalculate();
    }


    void Text::rotate(float rotation)
    {
        this->rotation += rotation;
        this->recalculate();
    }


    float Text::getRotation()
    {
        return this->rotation;
    }


    void Text::setRotation(float rotation)
    {
        this->rotation = rotation;
        this->recalculate();
    }


    void Text::setDepth(float depth)
    {
        this->depth = depth;
        this->recalculate();
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
        this->getGlyphs();
        this->recalculate();
    }
}