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

        void initialize();
        void update(float elapsedTime);
        void draw();
        void addMenu(std::string name);
        void addElement(std::string menuName, std::string name, IMenuElement* element);
        void attachCallback(std::string menuName, std::string elementName, std::string eventName, MenuCallback callback);
        void changeMenu(std::string menuName);
        IMenuElement* getElement(std::string menuName, std::string elementName);
    };
}