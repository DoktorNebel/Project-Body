#pragma once

#include "Rectangle.h"
#include "Vector2.h"
#include <vector>

namespace se
{
    struct Glyph
    {
        unsigned int width;
        unsigned int height;
        unsigned int advance;
        se::Vector2 offset;
        Rectangle textureRect;
        char character;
        std::vector<int> kerningAdvances;
        std::vector<char> kerningChars;
    };
}