#include "MenuSystem.h"

namespace se
{
    void MenuSystem::update(float elapsedTime)
    {
        for (unsigned int i = 0; i < this->menus.size(); ++i)
        {
            this->menus[i].update(elapsedTime);
            std::vector<MenuMessage> messages = this->menus[i].getMessages();
            for (unsigned int j = 0; j < messages.size(); ++j)
            {

            }
        }
    }
}