#include "EditorScene.h"

#include "EditorMenus.h"

namespace be
{
    void EditorScene::initialize()
    {
        se::Engine::setActiveCamera(this->camera);

        this->level.initializeEmpty(((be::MenuData*)se::Engine::getMenu()->data)->levelType);
    }


    void EditorScene::update(float elapsedTime)
    {
        //this->level.update(elapsedTime);
    }


    void EditorScene::draw()
    {
        this->level.draw();
    }


    void EditorScene::close()
    {

    }
}