#pragma once

#include <vector>
#include "Sprite.h"
#include "Polygon.h"
#include "Color.h"

namespace se
{
    class Content
    {
    private:

        static std::vector<std::string> spriteNames;
        static std::vector<Sprite> sprites;
        static std::vector<Polygon> hitboxes;

    private:

        Content();
        ~Content();

    private:

        static std::vector<se::Vector2> generateHitbox(se::Color* image, se::Sprite& sprite, char alphaTolerance, float angleTolerance);

    public:

        static void loadTextures(std::vector<unsigned int>& ids, std::vector<Vector2>& sizes);
        static Sprite getSprite(std::string name);
        static Polygon getHitbox(std::string spriteName);
    };
}