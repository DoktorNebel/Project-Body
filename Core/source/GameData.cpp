#include "GameData.h"

namespace bc
{
    unsigned int GameData::score = 0;
    float GameData::multiplier = 1.0f;
    int GameData::lives = 1;
    float GameData::humanInfection = 0.0f;
    unsigned int GameData::currentLevel = 1;

    void GameData::addScore(unsigned int score)
    {
        GameData::score += (unsigned int)(score * GameData::multiplier);
    }
}