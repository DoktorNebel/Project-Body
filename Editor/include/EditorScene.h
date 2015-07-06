#pragma once

#include "IScene.h"
#include "Level.h"

namespace be
{
    class EditorScene : public se::IScene
    {
    private:

        se::Camera camera;
        bc::Level level;

    public:

        virtual void initialize();
        virtual void update(float elapsedTime);
        virtual void draw();
        virtual void close();
    };
}