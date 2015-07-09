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

        struct SpawnData
        {
            std::string enemyName;
            std::string movementPattern;
            se::Vector2 position;
            se::Sprite sprite;
            se::Sprite arrowSprite;
        };

    private:

        se::Camera camera;
        bc::Level level;
        std::string currentTile;
        se::Sprite tileSprite;
        std::string currentEnemy;
        se::Sprite enemySprite;
        se::Sprite arrowSprite;
        std::vector<WallData> wallData;
        float currentTime;
        std::vector<float> spawnTimes;
        std::vector<std::vector<SpawnData>> spawnData;
        se::Rectangle playfield;
		std::vector<se::Sprite> lines;
		unsigned int highestId;
		std::vector<unsigned int> freeIds;

    private:

        SpawnData makeSpawnData();

    public:
		
		void load(std::string level);
        void save();
        virtual void initialize();
        virtual void update(float elapsedTime);
        virtual void draw();
        virtual void close();
    };
}