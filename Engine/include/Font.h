#pragma once

#include <vector>
#include "Glyph.h"

namespace se
{
    class Font
    {
    private:

        unsigned int texture;
        unsigned int size;
        unsigned int height;
        std::vector<char> characters;
        std::vector<Glyph> glyphs;

    public:

        Font(std::string path);

    public:

        unsigned int getTextureId();
        unsigned int getHeight();
        Glyph getGlyph(char character);
    };
}