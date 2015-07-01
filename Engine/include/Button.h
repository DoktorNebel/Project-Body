#pragma once

#include "IMenuElement.h"

namespace se
{
    class Button : public IMenuElement
    {
    private:

        Button* neighbours[4];
        Sprite sprite;
        Text text;

    public:

        Button();
        Button(Sprite sprite, Text text);

    private:

        void initialize();

    public:

        virtual void update(float elapsedTime);
        virtual void draw();
        void setNeighbours(Button* left, Button* right, Button* up, Button* down);
    };
}