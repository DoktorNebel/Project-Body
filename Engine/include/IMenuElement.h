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
        bool visible;

    private:

        virtual void initialize(MenuSystem* menuSystem) = 0;
        virtual void update(float elapsedTime) = 0;
        virtual void draw() = 0;
        
    protected:

        void callEvent(std::string eventName);

    public:

        void highlight();
        void unhighlight();
        void doInitialize(MenuSystem* menuSystem, bool highlighted);
        void doUpdate(float elapsedTime);
        void doDraw();
        void attachCallback(std::string eventName, MenuCallback* callback);
        void setNeighbours(IMenuElement* left, IMenuElement* right, IMenuElement* up, IMenuElement* down);
        void show();
        void hide();
    };
}