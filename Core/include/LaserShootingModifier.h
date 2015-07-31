#pragma once

#include "PlayerShootingModifier.h"

#include <vector>

#include "LaserModifier.h"

namespace bc
{
    class LaserShootingModifier : public PlayerShootingModifier
    {
    private:

        std::vector<LaserModifier*> lasers;
        std::string spriteNames[3];
        bool shooting;

    public:

        LaserShootingModifier(int level);

    private:

        virtual void shoot(float elapsedTime);
        virtual void setLevel();

    public:

        void stopShooting();
    };
}