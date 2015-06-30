#pragma once

#include <vector>
#include <string>
#include "Sprite.h"
#include "Text.h"
#include "IMenuElement.h"

namespace se
{
    class Menu
    {
    private:

        std::vector<std::string> elementNames;
        std::vector<IMenuElement*> elements;

    public:

        Menu();
        ~Menu();

    public:

        void update(float elapsedTime);
        void addElement(std::string name, IMenuElement* element);
        std::vector<Sprite> getSprites();
        std::vector<Text> getTexts();
        std::vector<MenuMessage> getMessages();
    };
}