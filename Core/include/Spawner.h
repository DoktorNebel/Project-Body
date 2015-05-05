#pragma once

#include <vector>
#include "Vector2.h"
#include "Entity.h"
#include "Collisiongroup.h"

namespace bc
{
    class Spawner
    {
    private:

        struct Spawn
        {
            se::Vector2 position;
            Entity entity;
            CollisionGroup::Type collisionGroup;
        };

    private:

        static std::vector<float> spawnTimes;
        static std::vector<Spawn> timedSpawns;
        static std::vector<Spawn> immediateSpawns;
        static float totalElapsedTime;
        static std::vector<std::vector<se::Rectangle>>* hitboxes;
        static std::vector<std::vector<bc::Entity>>* entities;

    public:

        static void initialize(std::vector<std::vector<se::Rectangle>>* hitboxes, std::vector<std::vector<bc::Entity>>* entities);
        static void update(float elapsedTime);
        static void spawn(se::Vector2 position, Entity entity, CollisionGroup::Type collisionGroup);
    };
}