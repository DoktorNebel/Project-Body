#pragma once

#include "IMenuElement.h"

namespace se
{
    class MenuTimer : public IMenuElement
    {
    private:

        float timer;
        float tickRate;

    public:

        MenuTimer(float tickRate = 1.0f);

    private:

        virtual void initialize(MenuSystem* menuSystem);
        virtual void update(float elapsedTime);
        virtual void draw();
    };
}