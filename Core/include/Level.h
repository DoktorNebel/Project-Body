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

        std::vector<std::vector<se::Rectangle>> hitboxes;
        std::vector<std::vector<bc::Entity>> entities;
        std::vector<std::pair<CollisionGroup::Type, CollisionGroup::Type>> collisionConfigs;
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