#pragma once

#include <string>
#include <vector>
#include "MenuMessage.h"
#include "Sprite.h"
#include "Text.h"

namespace se
{
    class IMenuElement
    {
    protected:

        std::vector<Sprite> sprites;
        std::vector<Text> texts;
        std::vector<MenuMessage> messages;

    public:

        virtual void update(float elapsedTime) = 0;
        std::vector<Sprite>& getSprites();
        std::vector<Text>& getTexts();
        std::vector<MenuMessage>& getMessages();
    };
}