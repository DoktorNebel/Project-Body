#include "IMenuElement.h"

#include "Input.h"
#include "MenuInputActions.h"
#include "Engine.h"

namespace se
{
    void IMenuElement::highlight()
    {
        this->highlighted = true;
        this->callEvent("onHighlight");
    }


    void IMenuElement::unhighlight()
    {
        this->highlighted = false;
        this->callEvent("onUnhighlight");
    }


    void IMenuElement::callEvent(std::string eventName)
    {
        unsigned int pos = std::find(this->eventNames.begin(), this->eventNames.end(), eventName) - this->eventNames.begin();
        if (pos < this->events.size())
            this->events[pos].call();
    }


    void IMenuElement::doInitialize(MenuSystem* menuSystem, bool highlighted)
    {
        this->show();
        this->eventNames.push_back("onHighlight");
        this->eventNames.push_back("onUnhighlight");

        this->initialize(menuSystem);

        for (unsigned int i = 0; i < this->eventNames.size(); ++i)
        {
            this->events.push_back(MenuEvent(this, menuSystem));
        }

        if (highlighted)
        {
            this->highlighted = true;
            this->callEvent("onHighlight");
        }
    }


    void IMenuElement::doUpdate(float elapsedTime)
    {
        if (this->visible)
        {
            this->update(elapsedTime);
            if (this->highlighted)
            {
                if (this->neighbours[LEFT_NEIGHBOUR] && Input::actionPressed(InputAction::MenuLeft))
                    Engine::getMenu()->highlight(this->neighbours[LEFT_NEIGHBOUR]);
                if (this->neighbours[RIGHT_NEIGHBOUR] && Input::actionPressed(InputAction::MenuRight))
                    Engine::getMenu()->highlight(this->neighbours[RIGHT_NEIGHBOUR]);
                if (this->neighbours[UP_NEIGHBOUR] && Input::actionPressed(InputAction::MenuUp))
                    Engine::getMenu()->highlight(this->neighbours[UP_NEIGHBOUR]);
                if (this->neighbours[DOWN_NEIGHBOUR] && Input::actionPressed(InputAction::MenuDown))
                    Engine::getMenu()->highlight(this->neighbours[DOWN_NEIGHBOUR]);
            }
        }
    }


    void IMenuElement::doDraw()
    {
        if (this->visible)
            this->draw();
    }


    void IMenuElement::attachCallback(std::string eventName, MenuCallback* callback)
    {
        unsigned int pos = std::find(this->eventNames.begin(), this->eventNames.end(), eventName) - this->eventNames.begin();
        if (pos < this->events.size())
            this->events[pos].callbacks.push_back(callback);
    }


    void IMenuElement::setNeighbours(IMenuElement* left, IMenuElement* right, IMenuElement* up, IMenuElement* down)
    {
        this->neighbours[LEFT_NEIGHBOUR] = left;
        this->neighbours[RIGHT_NEIGHBOUR] = right;
        this->neighbours[UP_NEIGHBOUR] = up;
        this->neighbours[DOWN_NEIGHBOUR] = down;
    }


    void IMenuElement::show()
    {
        this->visible = true;
    }


    void IMenuElement::hide()
    {
        this->visible = false;
    }
}