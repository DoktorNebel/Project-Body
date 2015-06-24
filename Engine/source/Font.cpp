#include "Font.h"

namespace se
{
    Font::Font(unsigned int texture, unsigned int size, unsigned int height, std::vector<char>& characters, std::vector<Glyph>& glyphs)
        : texture(texture)
        , size(size)
        , height(height)
        , characters(characters)
        , glyphs(glyphs)
    {

    }


    unsigned int Font::getTextureId()
    {
        return this->texture;
    }


    unsigned int Font::getHeight()
    {
        return this->height;
    }


    Glyph Font::getGlyph(char character)
    {
        unsigned int pos = std::find(this->characters.begin(), this->characters.end(), character) - this->characters.begin();
        if (pos < this->glyphs.size())
            return this->glyphs[pos];

        return this->glyphs[0];
    }
}