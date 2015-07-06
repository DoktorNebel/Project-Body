#pragma once

#include "IScene.h"

namespace be
{
    class StartScene : public se::IScene
    {
        virtual void initialize();
        virtual void update(float elapsedTime);
        virtual void draw();
        virtual void close();
    };
}