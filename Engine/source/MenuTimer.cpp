#include "MenuTimer.h"

namespace se
{
    MenuTimer::MenuTimer(float tickRate)
        : timer(0.0f)
        , tickRate(tickRate)
    {

    }


    void MenuTimer::initialize(MenuSystem* menuSystem)
    {
        this->eventNames.push_back("onTick");
    }


    void MenuTimer::update(float elapsedTime)
    {
        this->timer += elapsedTime;
        if (this->timer >= this->tickRate)
        {
            this->timer = 0.0f;
            this->callEvent("onTick");
        }
    }


    void MenuTimer::draw()
    {

    }
}