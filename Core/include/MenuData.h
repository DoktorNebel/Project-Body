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
        char playerName[4];
        unsigned int currentChar;
    };
}