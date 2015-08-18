#pragma once

#include "IScene.h"

namespace bg
{
    class MenuScene : public se::IScene
    {
    private:

        se::Sprite background;

    public:

        MenuScene(se::Sprite background);
        ~MenuScene();

    public:

        virtual void initialize();
        virtual void update(float elapsedTime);
        virtual void draw();
        virtual void close();
        void setBackground(se::Sprite newBackground);
    };
}