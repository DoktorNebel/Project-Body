#pragma once

#include "IModifier.h"

#include <vector>
#include "ShootingModifier.h"

namespace bc
{
    class BossPartModifier;

    class BossModifier : public IModifier
    {
    public:

        struct BossPattern
        {
            struct Phase
            {
                struct Spawn
                {
                    se::Vector2 position;
                    std::string enemyName;
                    std::string movePatternName;
                    float delay;
                };

                struct Part
                {
                    int id;
                    se::Vector2 spawnPosition;
                    std::string spriteName;
                    std::string movePatternName;
                };

                ShootingModifier::ShotPattern shotPattern;
                std::vector<Spawn> spawns;
                std::vector<Part> parts;
            };

            std::vector<Phase> phases;
        };

    private:

        std::vector<BossPartModifier*> parts;
        ShootingModifier* shootingModifier;

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}