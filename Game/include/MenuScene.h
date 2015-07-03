#pragma once

#include "IScene.h"

namespace bg
{
    class MenuScene : public se::IScene
    {
    public:

        MenuScene();
        ~MenuScene();

    public:

        virtual void initialize();
        virtual void update(float elapsedTime);
        virtual void draw();
        virtual void close();
    };
}