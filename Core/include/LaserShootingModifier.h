#pragma once

#include "PlayerShootingModifier.h"

#include <vector>

#include "LaserModifier.h"

namespace bc
{
    class LaserShootingModifier : public PlayerShootingModifier
    {
    private:

        PlayerShootingModifier* previousShot;
        float timer;
        std::vector<LaserModifier*> lasers;

    public:

        LaserShootingModifier();

    private:

        virtual void shoot(float elapsedTime);
        virtual void setLevel();
    };
}