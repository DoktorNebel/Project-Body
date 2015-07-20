#pragma once

#include "PlayerShootingModifier.h"

namespace bc
{
    class NormalShootingModifier : public PlayerShootingModifier
    {
    private:

        float fireRate;
        float fireCounter;
        std::vector<se::Vector2> shootingOffsets;

    public:

        NormalShootingModifier(int level);

    private:
    
        virtual void shoot(float elapsedTime);
        virtual void setLevel();
    };
}