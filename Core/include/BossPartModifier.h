#pragma once

#include "IModifier.h"

#include <string>

#include "Sprite.h"
#include "Sound.h"

namespace bc
{
    class BossModifier;

    class BossPartModifier : public IModifier
    {
    private:

        BossModifier* boss;
        float health;
        se::Sprite destroyedSprite;
        bool hasDestroyedSprite;
        bool destroyed;
		bool hittable;
        se::Sound explosionSound;

    public:

        int id;

    public:

        BossPartModifier(BossModifier* boss, float health, std::string spriteName);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}