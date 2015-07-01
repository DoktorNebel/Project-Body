#include "MenuEvent.h"

namespace se
{
    MenuEvent::MenuEvent(IMenuElement* owner, MenuSystem* menuSystem)
        : owner(owner)
        , menuSystem(menuSystem)
    {

    }


    void MenuEvent::call()
    {
        for (unsigned int i = 0; i < this->callbacks.size(); ++i)
        {
            this->callbacks[i](this->owner, this->menuSystem);
        }
    }
}