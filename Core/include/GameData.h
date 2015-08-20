#pragma once

namespace bc
{
    class GameData
    {
    public:

        struct Highscore
        {
            char name[4];
            unsigned int score;
        };

    public:

        static unsigned int score;
        static float multiplier;
        static int lives;
        static bool playerDead;
        static float humanInfection;
        static unsigned int currentLevel;
        static Highscore scores[40];

    public:

        static void addScore(unsigned int score);
        static void reset();
		static void loadScores();
		static void saveScores();
    };
}