#pragma once

#include "IModifier.h"
#include "Vector2.h"
#include "AnimatedSprite.h"

namespace bc
{
    class AnimatedParticleModifier : public IModifier
    {
    private:

        se::Vector2 velocity;
        float lifeTime;
        float startLifeTime;
        se::Vector2 size;
        se::AnimatedSprite sprite;

    public:

        AnimatedParticleModifier(se::Vector2 velocity, se::Vector2 size, se::AnimatedSprite sprite);
        ~AnimatedParticleModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}