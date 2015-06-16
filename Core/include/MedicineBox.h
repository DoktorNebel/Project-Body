#pragma once

#include "PlayerModifier.h"

namespace bc
{
    class MedicineBox
    {
    public:

        float gamespeed;
        PlayerModifier* player;
        float cooldowns[3];
        float cooldownTimers[3];

    public:

        MedicineBox(PlayerModifier* player);

    public:

        void update(float elapsedTime);
    };
}