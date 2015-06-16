#pragma once

#include "IModifier.h"

#include "PlayerModifier.h"

namespace bc
{
    class PlayerSatelliteModifier : public IModifier
    {
    private:

        PlayerModifier* player;
        float currentOrbitPosition;
        float fireRate;
        float fireCounter;
        float lifeTime;

    public:

        PlayerSatelliteModifier(PlayerModifier* player);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}