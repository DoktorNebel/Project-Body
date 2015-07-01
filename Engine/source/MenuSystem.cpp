#include "MenuSystem.h"

namespace se
{
    void MenuSystem::update(float elapsedTime)
    {
        for (unsigned int i = 0; i < this->menus.size(); ++i)
        {
            this->menus[i].update(elapsedTime);
        }
    }


    void MenuSystem::draw()
    {
        for (unsigned int i = 0; i < this->menus.size(); ++i)
        {
            this->menus[i].draw();
        }
    }


    void MenuSystem::attachCallback(std::string menuName, std::string elementName, std::string eventName, MenuCallback callback)
    {
        unsigned int pos = std::find(this->menuNames.begin(), this->menuNames.end(), menuName) - this->menuNames.begin();
        if (pos < this->menus.size())
            this->menus[pos].attachCallback(elementName, eventName, callback);
    }
}