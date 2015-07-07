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
			bc::Entity entityCopy;
        };

    private:

        se::Camera camera;
        bc::Level level;
        std::string currentTile;
        se::Sprite tileSprite;
        std::vector<WallData> wallData;
		std::vector<se::Sprite> lines;
		unsigned int highestId;
		std::vector<unsigned int> freeIds;

    public:
		
		void load(std::string level);
        void save();
        virtual void initialize();
        virtual void update(float elapsedTime);
        virtual void draw();
        virtual void close();
    };
}