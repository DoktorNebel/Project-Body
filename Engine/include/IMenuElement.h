#pragma once

#include <string>
#include <vector>
#include "MenuEvent.h"
#include "Sprite.h"
#include "Text.h"

#define LEFT_NEIGHBOUR 0
#define RIGHT_NEIGHBOUR 1
#define UP_NEIGHBOUR 2
#define DOWN_NEIGHBOUR 3

namespace se
{
    class IMenuElement
    {
    protected:

        IMenuElement* neighbours[4];
        std::vector<std::string> eventNames;
        std::vector<MenuEvent> events;
        bool highlighted;
        
    protected:

        void highlight();
        bool unhighlight();
        void callEvent(std::string eventName);

    public:

        virtual void initialize(MenuSystem* menuSystem) = 0;
        virtual void update(float elapsedTime) = 0;
        virtual void draw() = 0;
        void attachCallback(std::string eventName, MenuCallback callback);
        void setNeighbours(IMenuElement* left, IMenuElement* right, IMenuElement* up, IMenuElement* down);
    };
}