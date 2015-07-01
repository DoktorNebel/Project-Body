#pragma once

#include <string>
#include <vector>
#include "MenuEvent.h"
#include "Sprite.h"
#include "Text.h"

namespace se
{
    class IMenuElement
    {
    protected:

        std::vector<std::string> eventNames;
        std::vector<MenuEvent> events;

    public:

        virtual void update(float elapsedTime) = 0;
        virtual void draw() = 0;
        void attachCallback(std::string eventName, MenuCallback callback);
    };
}