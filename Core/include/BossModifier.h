#pragma once

#include "IModifier.h"

#include <vector>
#include "ShootingModifier.h"
#include "MovementPatternModifier.h"

namespace bc
{
    class BossPartModifier;

    class BossModifier : public IModifier
    {
    public:

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
                se::Vector2 spawnPosition;
                std::string spriteName;
                std::string movePatternName;
                bool noRotate;
                std::string shotPatternName;
            };

            std::string movementPattern;
            MovementPatternModifier::Style::Type movementType;
            std::string shotPattern;
            std::vector<Spawn> spawns;
            std::vector<Part> parts;
            float startHealth;
        };

    private:

        std::vector<Phase> phases;
        unsigned int nextPhase;
        std::vector<BossPartModifier*> parts;
		float explodingTimer;
		float coinTimer;
		bool dying;

    public:

        BossModifier(std::vector<Phase> pattern);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}