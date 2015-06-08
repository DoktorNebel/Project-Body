#pragma once

#include "IModifier.h"

#include <string>
#include <vector>

namespace bc
{
    class ShootingModifier : public IModifier
    {
    public:

        struct ShotPattern
        {
            struct Salvo
            {
                std::vector<std::string> shotSpriteNames;
                std::vector<std::string> shotMovementNames;
                std::vector<float> rotations;
                std::vector<float> speeds;
            };

            std::vector<Salvo> shotSalvos;
            std::vector<float> delays;
        };

    private:

        ShotPattern shotPattern;
        float timer;
        unsigned int currentSalvo;

    public:

        ShootingModifier(ShotPattern pattern);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}