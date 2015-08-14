#pragma once

#include <string>

namespace bg
{
    struct MenuData
    {
        std::string levelName;
        float stickyShotCooldown;
        float bombRingCooldown;
        float bossHealth;
    };
}