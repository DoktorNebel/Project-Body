#pragma once

#include "IScene.h"
#include "Level.h"
#include <vector>

namespace be
{
    class EditorScene : public se::IScene
    {
    private:

        struct WallData
        {
            std::string spritename;
            se::Vector2 position;
        };

    private:

        se::Camera camera;
        bc::Level level;
        std::string currentTile;
        se::Sprite tileSprite;
        std::vector<WallData> wallData;

    public:

        void save();
        virtual void initialize();
        virtual void update(float elapsedTime);
        virtual void draw();
        virtual void close();
    };
}