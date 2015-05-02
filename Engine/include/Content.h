#pragma once

#include <vector>
#include "Sprite.h"

namespace se
{
    class Content
    {
    private:

        static std::vector<std::string> spriteNames;
        static std::vector<Sprite> sprites;

    private:

        Content();
        ~Content();

    public:

        static void loadTextures(std::vector<unsigned int>& ids, std::vector<Vector2>& sizes);
        static Sprite getSprite(std::string name);
    };
}