#pragma once

#include <vector>
#include "Sprite.h"
#include "Polygon.h"
#include "Color.h"
#include "Font.h"
#include "Sound.h"

namespace se
{
    class Content
    {
    private:

        struct Image
        {
            int x;
            int y;
            int n;
            unsigned char* data;
            std::string spriteName;
            se::Rectangle textureRect;
            unsigned int texture;
        };

    private:

        static std::vector<std::string> spriteNames;
        static std::vector<Sprite> sprites;
        static std::vector<Polygon> hitboxes;
        static std::vector<std::string> fontNames;
        static std::vector<Font> fonts;
        static std::vector<std::string> soundNames;
        static std::vector<Sound> sounds;

    private:

        Content();
        ~Content();

    private:

        static std::vector<se::Vector2> generateHitbox(se::Color* image, int imageWidth, int imageHeight, char alphaTolerance, float angleTolerance);
        static void generateSpriteBorder(se::Color* image, int startX, int startY, int imageWidth, int imageHeight);
        static void loadWav(std::string path, unsigned int bufferId);

    public:

        static void loadTextures(std::vector<unsigned int>& ids, std::vector<Vector2>& sizes);
        static void loadFonts(std::vector<unsigned int>& ids, std::vector<Vector2>& sizes);
        static void loadSounds(std::vector<unsigned int>& ids);
        static Sprite getSprite(std::string name);
        static Polygon getHitbox(std::string spriteName);
        static Font* getFont(std::string name);
        static Sound getSound(std::string name);
    };
}