#include "EditorScene.h"

#include "EditorMenus.h"
#include "Input.h"
#include "EditorInputActions.h"
#include "MathFunctions.h"
#include "Spawner.h"
#include "MenuInputActions.h"
#include <direct.h>

namespace be
{
    EditorScene::SpawnData EditorScene::makeSpawnData()
    {
        SpawnData data;
        data.sprite = this->enemySprite;
        data.sprite.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        data.arrowSprite = this->arrowSprite;
        data.arrowSprite.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        data.position = this->enemySprite.getPosition() - se::Vector2(this->playfield.left + (this->playfield.right - this->playfield.left) / 2.0f, this->playfield.bottom + (this->playfield.top - this->playfield.bottom) / 2.0f);
        if (this->currentEnemy == "Virus1")
        {
            data.enemyName = "Virus";
            data.movementPattern = "Down_Straight";
        }
        else if (this->currentEnemy == "V1")
        {
            data.enemyName = "Big_Virus";
            data.movementPattern = "Down_Straight";
        }
        else if (this->currentEnemy == "KillaBug1")
        {
            data.enemyName = "Bug";
            data.movementPattern = "Down_Wait";
        }
        else if (this->currentEnemy == "Kefer")
        {
            data.enemyName = "Little_Bug";
            data.movementPattern = "Seek_Player_Delayed";
        }
        else if (this->currentEnemy == "Popel")
        {
            data.enemyName = "Booger";
            data.movementPattern = "None";
        }
        else if (this->currentEnemy == "ShooterHead")
        {
            data.enemyName = "Shooter";
            data.movementPattern = "None";
        }
        else if (this->currentEnemy == "Boss1")
        {
            data.enemyName = "Boss1";
            data.movementPattern = "Boss1";
        }

        return data;
    }


	void EditorScene::load(std::string level)
	{
		this->level.initialize(level);
	}


    void EditorScene::save()
    {
        _mkdir("../SavedLevels");
        _mkdir("../SavedLevels/Test");
        FILE* file = fopen("../SavedLevels/Test/Walls.txt", "w");

        for (unsigned int i = 0; i < this->wallData.size(); ++i)
        {
            fprintf(file, "%s %f %f\n", this->wallData[i].spritename.c_str(), this->wallData[i].position.x, this->wallData[i].position.y);
        }

        fclose(file);


        file = fopen("../SavedLevels/Test/Enemies.txt", "w");

        for (unsigned int i = 0; i < this->spawnTimes.size(); ++i)
        {
            for (unsigned int j = 0; j < this->spawnData[i].size(); ++j)
            {
                fprintf(file, "%s %s %f %f %f\n", this->spawnData[i][j].enemyName.c_str(), this->spawnData[i][j].movementPattern.c_str(), this->spawnTimes[i], this->spawnData[i][j].position.x, this->spawnData[i][j].position.y);
            }
        }

        fclose(file);
    }


    void EditorScene::initialize()
    {
        this->level.initializeEmpty(((be::MenuData*)se::Engine::getMenu()->data)->levelType);

        se::Engine::setActiveCamera(this->camera);

        ((be::MenuData*)se::Engine::getMenu()->data)->scene = this;

		se::Sprite line = se::Content::getSprite("Pixel");
		line.setColor(se::Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		line.setScale(se::Vector2(512.0f * 4.5f, 3.0f));
		line.setPosition(se::Vector2(0, se::Engine::getSettings().renderResolutionHeight / 2));
		this->lines.push_back(line);
		line.setPosition(se::Vector2(0, -(int)se::Engine::getSettings().renderResolutionHeight / 2));
		this->lines.push_back(line);
		line.setScale(se::Vector2(3.0f, 720.0f));
		line.setPosition(se::Vector2(-512.0f * 2.25f, 0.0f));
		this->lines.push_back(line);
		line.setPosition(se::Vector2(512.0f * 2.25f, 0.0f));
		this->lines.push_back(line);

        this->playfield = se::Rectangle((float)se::Engine::getSettings().renderResolutionHeight / 2.0f, -(float)se::Engine::getSettings().renderResolutionHeight / 2.0f, -512.0f * 2.25f, 512.0f * 2.25f);

		this->highestId = 1;

        this->arrowSprite = se::Content::getSprite("Arrow");
        this->arrowSprite.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 0.5f));

        this->currentTime = 0.0f;
    }


    void EditorScene::update(float elapsedTime)
    {
        this->level.update(0.0f);
        if (((be::MenuData*)se::Engine::getMenu()->data)->currentTile != this->currentTile)
        {
            this->currentTile = ((be::MenuData*)se::Engine::getMenu()->data)->currentTile;
            if (this->currentTile != "")
            {
                this->tileSprite = se::Content::getSprite(this->currentTile);
                this->tileSprite.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 0.5f));
            }
        }

        if (this->currentTile != "")
        {
            se::Vector2 pos = se::Input::getMousePos();
            pos += this->camera.getPosition() * se::Vector2((float)se::Engine::getSettings().renderResolutionWidth / 2.0f, (float)se::Engine::getSettings().renderResolutionHeight / 2.0f);
            //se::Vector2 origin(pos.x - this->tileSprite.getWidth() / 2.0f, pos.y - this->tileSprite.getHeight() / 2.0f);
            int xRem = (int)pos.x % 64;
            int yRem = (int)pos.y % 64;
            pos += se::Vector2(xRem < 32 ? -xRem : 64 - xRem, yRem < 32 ? -yRem : 64 - yRem);
            if (this->tileSprite.getWidth() == 128.0f)
                pos += se::Vector2(32, -32);
            pos.x = floor(pos.x);
            pos.y = floor(pos.y);
            this->tileSprite.setPosition(pos);

            if (se::Input::actionPressed(se::InputAction::MenuClick))
            {
                WallData data;
                data.spritename = this->currentTile;
                data.position = this->tileSprite.getPosition();
				data.entityCopy = bc::Entity(this->tileSprite, std::vector<bc::IModifier*>());
				unsigned int id;
				if (this->freeIds.size() > 0)
				{
					id = this->freeIds.back();
					this->freeIds.pop_back();
				}
				else
				{
					id = ++this->highestId;
				}
				data.entityCopy.id = id;

                this->wallData.push_back(data);
                bc::Spawner::spawn(this->tileSprite.getPosition(), this->currentTile, std::vector<bc::IModifier*>(), bc::CollisionGroup::LevelElements);
            }

			if (se::Input::actionPressed(be::InputActions::DeleteTile))
			{
				unsigned int index = this->wallData.size();
				for (unsigned int i = 0; i < this->wallData.size(); ++i)
				{
					if (se::Math::Distance(this->wallData[i].position, pos) < 64.0f)
					{
						index = i;
						break;
					}
				}

				if (index < this->wallData.size())
				{
					bc::Spawner::kill(this->wallData[index].entityCopy, bc::CollisionGroup::LevelElements);
					this->freeIds.push_back(this->wallData[index].entityCopy.id);
					this->wallData.erase(this->wallData.begin() + index);
				}
			}
        }


        if (this->currentTime != ((be::MenuData*)se::Engine::getMenu()->data)->currentTime)
        {
            this->playfield.move(se::Vector2(0.0f, ((be::MenuData*)se::Engine::getMenu()->data)->currentTime - this->currentTime) * 100.0f);
            for (unsigned int i = 0; i < this->lines.size(); ++i)
            {
                this->lines[i].move(se::Vector2(0.0f, ((be::MenuData*)se::Engine::getMenu()->data)->currentTime - this->currentTime) * 100.0f);
            }
            this->currentTime = ((be::MenuData*)se::Engine::getMenu()->data)->currentTime;
        }


        if (((be::MenuData*)se::Engine::getMenu()->data)->currentEnemy != this->currentEnemy)
        {
            this->currentEnemy = ((be::MenuData*)se::Engine::getMenu()->data)->currentEnemy;
            if (this->currentEnemy != "")
            {
                this->enemySprite = se::Content::getSprite(this->currentEnemy);
                this->enemySprite.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 0.5f));
            }
        }

        if (this->currentEnemy != "")
        {
            se::Vector2 mousePos = se::Input::getMousePos();
            mousePos += this->camera.getPosition() * se::Vector2((float)se::Engine::getSettings().renderResolutionWidth / 2.0f, (float)se::Engine::getSettings().renderResolutionHeight / 2.0f);
            se::Vector2 pos(this->playfield.left, mousePos.y);
            this->arrowSprite.setRotation(90.0f);
            this->enemySprite.setRotation(90.0f);
            this->arrowSprite.setPosition(pos + se::Vector2(50.0f, 0.0f));
            this->enemySprite.setPosition(pos + se::Vector2(-enemySprite.getHeight() * 0.6f, 0.0f));
            float minDist = abs(mousePos.x - this->playfield.left);
            if (abs(mousePos.x - this->playfield.right) < minDist)
            {
                minDist = abs(mousePos.x - this->playfield.right);
                pos = se::Vector2(this->playfield.right, mousePos.y);
                this->arrowSprite.setRotation(-90.0f);
                this->enemySprite.setRotation(-90.0f);
                this->arrowSprite.setPosition(pos + se::Vector2(-50.0f, 0.0f));
                this->enemySprite.setPosition(pos + se::Vector2(enemySprite.getHeight() * 0.6f, 0.0f));
            }
            if (abs(mousePos.y - this->playfield.top) < minDist)
            {
                minDist = abs(mousePos.y - this->playfield.top);
                pos = se::Vector2(mousePos.x, this->playfield.top);
                this->arrowSprite.setRotation(0.0f);
                this->enemySprite.setRotation(0.0f);
                this->arrowSprite.setPosition(pos + se::Vector2(0.0f, -50.0f));
                this->enemySprite.setPosition(pos + se::Vector2(0.0f, enemySprite.getHeight() * 0.6f));
            }
            if (abs(mousePos.y - this->playfield.bottom) < minDist)
            {
                pos = se::Vector2(mousePos.x, this->playfield.bottom);
                this->arrowSprite.setRotation(180.0f);
                this->enemySprite.setRotation(180.0f);
                this->arrowSprite.setPosition(pos + se::Vector2(0.0f, 50.0f));
                this->enemySprite.setPosition(pos + se::Vector2(0.0f, -enemySprite.getHeight() * 0.6f));
            }

            if (se::Input::actionPressed(se::InputAction::MenuClick))
            {
                unsigned int pos = this->spawnTimes.size();
                std::vector<float>::iterator iter = this->spawnTimes.begin();
                while (iter != this->spawnTimes.end() && *iter <= this->currentTime)
                {
                    if (this->currentTime - *iter < 0.05f)
                    {
                        pos = iter - this->spawnTimes.begin();
                        break;
                    }
                    ++iter;
                }
                if (pos < this->spawnTimes.size())
                {
                    this->spawnData[pos].push_back(this->makeSpawnData());
                }
                else
                {
                    pos = iter - this->spawnTimes.begin();
                    this->spawnTimes.insert(iter, this->currentTime);
                    this->spawnData.insert(this->spawnData.begin() + pos, std::vector<SpawnData>());
                    this->spawnData[pos].push_back(this->makeSpawnData());
                }
            }
        }


        this->camera.move(se::Vector2(-se::Input::getActionValue(InputActions::CameraLeft) * 500.0f * elapsedTime + se::Input::getActionValue(InputActions::CameraRight) * 500.0f * elapsedTime,
            se::Input::getActionValue(InputActions::CameraUp) * 500.0f * elapsedTime - se::Input::getActionValue(InputActions::CameraDown) * 500.0f * elapsedTime) / 
            se::Vector2((float)se::Engine::getSettings().renderResolutionWidth / 2.0f, (float)se::Engine::getSettings().renderResolutionHeight / 2.0f));
    }


    void EditorScene::draw()
    {
        this->level.draw();

		for (unsigned int i = 0; i < this->lines.size(); ++i)
		{
			se::Engine::draw(this->lines[i]);
		}

        if (this->currentTile != "")
            se::Engine::draw(this->tileSprite);

        if (this->currentEnemy != "")
        {
            se::Engine::draw(this->enemySprite);
            se::Engine::draw(this->arrowSprite);
        }

        unsigned int pos = this->spawnTimes.size();
        for (unsigned int i = 0; i < this->spawnTimes.size(); ++i)
        {
            if (abs(this->spawnTimes[i] - this->currentTime) < 1.0f)
                pos = i;
        }
        if (pos < this->spawnTimes.size())
        {
            for (unsigned int i = 0; i < this->spawnData[pos].size(); ++i)
            {
                se::Engine::draw(this->spawnData[pos][i].sprite);
                se::Engine::draw(this->spawnData[pos][i].arrowSprite);
            }
        }
    }


    void EditorScene::close()
    {

    }
}