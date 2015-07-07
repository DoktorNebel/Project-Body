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
    void EditorScene::save()
    {
        int bla = _mkdir("../SavedLevels");
        bla = _mkdir("../SavedLevels/Test");
        FILE* file = fopen("../SavedLevels/Test/Walls.txt", "w");

        for (unsigned int i = 0; i < this->wallData.size(); ++i)
        {
            fprintf(file, "%s %f %f\n", this->wallData[i].spritename.c_str(), this->wallData[i].position.x, this->wallData[i].position.y);
        }

        fclose(file);
    }


    void EditorScene::initialize()
    {
        this->level.initializeEmpty(((be::MenuData*)se::Engine::getMenu()->data)->levelType);

        se::Engine::setActiveCamera(this->camera);

        ((be::MenuData*)se::Engine::getMenu()->data)->scene = this;
    }


    void EditorScene::update(float elapsedTime)
    {
        this->level.update(0.0f);
        if (((be::MenuData*)se::Engine::getMenu()->data)->currentTile != this->currentTile)
        {
            this->currentTile = ((be::MenuData*)se::Engine::getMenu()->data)->currentTile;
            this->tileSprite = se::Content::getSprite(this->currentTile);
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
            this->tileSprite.setPosition(pos);

            if (se::Input::actionPressed(se::InputAction::MenuClick))
            {
                WallData data;
                data.spritename = this->currentTile;
                data.position = this->tileSprite.getPosition();
                this->wallData.push_back(data);
                bc::Spawner::spawn(this->tileSprite.getPosition(), this->currentTile, std::vector<bc::IModifier*>(), bc::CollisionGroup::LevelElements);
            }
        }

        this->camera.move(se::Vector2(-se::Input::getActionValue(InputActions::CameraLeft) * 500.0f * elapsedTime + se::Input::getActionValue(InputActions::CameraRight) * 500.0f * elapsedTime,
            se::Input::getActionValue(InputActions::CameraUp) * 500.0f * elapsedTime - se::Input::getActionValue(InputActions::CameraDown) * 500.0f * elapsedTime) / 
            se::Vector2((float)se::Engine::getSettings().renderResolutionWidth / 2.0f, (float)se::Engine::getSettings().renderResolutionHeight / 2.0f));
    }


    void EditorScene::draw()
    {
        this->level.draw();
        if (this->currentTile != "")
            se::Engine::draw(this->tileSprite);
    }


    void EditorScene::close()
    {

    }
}