#pragma once

#include "PlayerShootingModifier.h"

namespace bc
{
    class HomingShootingModifier : public PlayerShootingModifier
    {
    private:

        float fireRate;
        float fireCounter;
        std::vector<float> shootingDirections;

    public:

        HomingShootingModifier(int level);

    private:

        virtual void shoot(float elapsedTime);
        virtual void setLevel();
    };
}