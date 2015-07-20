#pragma once

#include "PlayerShootingModifier.h"
#include "MovementPatternModifier.h"

namespace bc
{
    class CurvyShootingModifier : public PlayerShootingModifier
    {
    private:

        float fireRate;
        float fireCounter;
        float curvyfireRate;
        float curvyfireCounter;
        std::vector<std::vector<MovementPatternModifier::Waypoint>> movementPatterns;

    public:

        CurvyShootingModifier(int level);

    private:

        virtual void shoot(float elapsedTime);
        virtual void setLevel();
    };
}