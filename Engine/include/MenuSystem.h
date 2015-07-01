#pragma once

#include <vector>
#include <string>
#include "Menu.h"

namespace se
{
    class MenuSystem
    {
    private:

        std::vector<std::string> menuNames;
        std::vector<Menu> menus;
        Menu* currentMenu;

    public:

        void update(float elapsedTime);
        void draw();
        void attachCallback(std::string menuName, std::string elementName, std::string eventName, MenuCallback callback);
    };
}