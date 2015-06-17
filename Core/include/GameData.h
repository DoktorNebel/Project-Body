#pragma once

namespace bc
{
    class GameData
    {
    public:

        static unsigned int score;
        static float multiplier;
        static int lives;
        static float humanInfection;
        static unsigned int currentLevel;

    public:

        static void addScore(unsigned int score);
    };
}