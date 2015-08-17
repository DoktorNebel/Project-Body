#include "GameData.h"

#include <Windows.h>
#include <Shlobj.h>
#include <string>

namespace bc
{
    unsigned int GameData::score = 0;
    float GameData::multiplier = 1.0f;
    int GameData::lives = 1;
    float GameData::humanInfection = 0.0f;
    unsigned int GameData::currentLevel = 1;
    GameData::Highscore GameData::scores[40];

    void GameData::addScore(unsigned int score)
    {
        GameData::score += (unsigned int)(score * GameData::multiplier);
    }


    void GameData::reset()
    {
        GameData::score = 0;
        GameData::multiplier = 1.0f;
        GameData::lives = 1;
    }


    void GameData::loadScores()
    {
        PWSTR widepath;
        SHGetKnownFolderPath(FOLDERID_Documents, 0, 0, &widepath);
        char documentsPath[256];
        wcstombs(documentsPath, widepath, 256);

        std::string path(documentsPath);
        path += "\\Games";
        CreateDirectory(path.c_str(), 0);
        path += "\\Body";
        CreateDirectory(path.c_str(), 0);
        path += "\\Highscores.sav";
        CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

        FILE* file = fopen(path.c_str(), "rb");

        unsigned int scoresRead = fread(scores, sizeof(Highscore), 40, file);

        fclose(file);

        for (unsigned int i = scoresRead; i < 40; ++i)
        {
            Highscore highscore;
            highscore.name[0] = ' ';
            highscore.name[1] = ' ';
            highscore.name[2] = ' ';
            highscore.name[3] = '\0';
            highscore.score = 0;

            GameData::scores[i] = highscore;
        }

        CoTaskMemFree(widepath);
    }


	void GameData::saveScores()
	{
		PWSTR widepath;
		SHGetKnownFolderPath(FOLDERID_Documents, 0, 0, &widepath);
		char documentsPath[256];
		wcstombs(documentsPath, widepath, 256);

		std::string path(documentsPath);
		path += "\\Games";
		CreateDirectory(path.c_str(), 0);
		path += "\\Body";
		CreateDirectory(path.c_str(), 0);
		path += "\\Highscores.sav";
		CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

		FILE* file = fopen(path.c_str(), "wb");

		fwrite(GameData::scores, sizeof(Highscore), 40, file);

		fclose(file);
	}
}