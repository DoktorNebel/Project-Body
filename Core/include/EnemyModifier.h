#pragma once

#include "IModifier.h"
#include "AnimatedSprite.h"

namespace bc
{
    class EnemyModifier : public IModifier
    {
    private:

        se::AnimatedSprite animatedSprite;
        se::Vector2 position;

    public:

        EnemyModifier(se::AnimatedSprite animatedSprite);
        ~EnemyModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup);
    };
}