#pragma once

#include <vector>
#include "Vector2.h"
#include "Entity.h"
#include "Collisiongroup.h"
#include "MovementPatternModifier.h"
#include "ShootingModifier.h"
#include "AnimatedSprite.h"
#include "BossModifier.h"

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
        static std::vector<Spawn> killList;
        static float totalElapsedTime;
        static std::vector<std::vector<se::Rectangle>>* hitboxes;
        static std::vector<std::vector<bc::Entity>>* entities;
        static unsigned int nextSpawn;
        static unsigned int highestId;
        static std::vector<unsigned int> freeIds;
        static std::vector<std::string> movementPatternNames;
        static std::vector<std::vector<MovementPatternModifier::Waypoint>> movementPatterns;
        static std::vector<std::string> shotPatternNames;
        static std::vector<ShootingModifier::ShotPattern> shotPatterns;
        static std::vector<std::string> animationNames;
        static std::vector<se::AnimatedSprite> animations;
        static std::vector<std::string> bossPatternNames;
        static std::vector<std::vector<BossModifier::Phase>> bossPatterns;
        static std::vector<float> bossHealth;

    public:

        static bool bossAlive;

    private:

        static Entity createEnemy(std::string name, std::string movementPattern, std::string shotPattern);
        static unsigned int getFreeId();

    public:

        static bool getAnimation(std::string name, se::AnimatedSprite* outSprite);
        static ShootingModifier::ShotPattern getShotPattern(std::string patternName);
        static std::vector<MovementPatternModifier::Waypoint> getMovementPattern(std::string patternName);
        static void initialize(std::vector<std::vector<se::Rectangle>>* hitboxes, std::vector<std::vector<bc::Entity>>* entities, std::string levelName = std::string());
        static void update(float elapsedTime);
        static void spawn(se::Vector2 position, std::string spriteName, std::vector<IModifier*> modifiers, CollisionGroup::Type collisionGroup);
        static void spawnEnemy(se::Vector2 position, std::string enemyName, std::string movePatternName, std::string shotPatternName);
        static void kill(Entity entity, CollisionGroup::Type collisionGroup);
        static std::vector<Entity>* getEntities(CollisionGroup::Type entityType);
    };
}