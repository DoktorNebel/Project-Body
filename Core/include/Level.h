#pragma once

#include <string>
#include <vector>
#include "Rectangle.h"
#include "Sprite.h"
#include "IEntity.h"
#include "Engine.h"
#include "Player.h"

namespace bc
{
    class Level
    {
    private:

        struct Index
        {
            enum Type
            {
                Players,
                Enemies,
                PlayerProjectiles,
                EnemyProjectiles,
                Items,
                LevelElements
            };
        };

    private:

        std::vector<std::vector<se::Rectangle>> hitboxes;
        std::vector<std::vector<bc::IEntity*>> entities;
        std::vector<std::pair<Index::Type, Index::Type>> collisionConfigs;
        se::Engine* engine;
        se::Camera camera;

    public:

        Level();
        ~Level();

    public:

        void initialize(std::string source, se::Engine* engine);
        void update(float elapsedTime);
        void draw();
    };
}