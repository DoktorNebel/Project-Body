#pragma once

#include <string>
#include <vector>
#include "Rectangle.h"
#include "Sprite.h"
#include "Entity.h"
#include "Engine.h"
#include "Collisiongroup.h"

namespace bc
{
    class Level
    {
    private:

        struct ScrollKey
        {
            float time;
            float speed;
        };

    private:

        std::vector<std::vector<se::Rectangle>> hitboxes;
        std::vector<std::vector<bc::Entity>> entities;
        std::vector<std::pair<CollisionGroup::Type, CollisionGroup::Type>> collisionConfigs;
        se::Camera camera;
        se::Vector2 lastCameraPos;
        float totalElapsedTime;
        unsigned int currentScrollKey;
        std::vector<ScrollKey> scrollSpeeds;
        std::vector<float> backgroundSpeeds;
        std::vector<std::vector<se::Sprite>> backgroundSprites;

    public:

        Level();
        ~Level();

    public:

        void initialize(std::string source);
        void update(float elapsedTime);
        void draw();
    };
}