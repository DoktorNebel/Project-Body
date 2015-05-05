#pragma once

#include "IModifier.h"

namespace bc
{
    class PlayerModifier : public IModifier
    {
    private:

        float speed;
        float fireRate;
        float fireCounter;

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity);
    };
}