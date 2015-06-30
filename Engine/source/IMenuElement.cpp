#include "IMenuElement.h"

namespace se
{
    std::vector<Sprite>& IMenuElement::getSprites()
    {
        return this->sprites;
    }


    std::vector<Text>& IMenuElement::getTexts()
    {
        return this->texts;
    }


    std::vector<MenuMessage>& IMenuElement::getMessages()
    {
        return this->messages;
    }
}