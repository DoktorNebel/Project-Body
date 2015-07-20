#pragma once

#include "PlayerShootingModifier.h"

namespace bc
{
    class SplitShootingModifier : public PlayerShootingModifier
    {
    private:

        float fireRate;
        float fireCounter;
        std::vector<float> shootingDirections;

    public:

        SplitShootingModifier(int level);

    private:

        virtual void shoot(float elapsedTime);
        virtual void setLevel();
    };
}