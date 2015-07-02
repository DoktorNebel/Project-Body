#include "IMenuElement.h"

namespace se
{
    void IMenuElement::highlight()
    {
        this->unhighlight();
        this->highlighted = true;
        this->callEvent("OnHighlight");
    }


    bool IMenuElement::unhighlight()
    {
        if (this->highlighted)
        {
            this->highlighted = false;
            return true;
        }
        else
        {
            for (unsigned int i = 0; i < 4; ++i)
            {
                if (this->neighbours[i] && this->neighbours[i]->unhighlight())
                    return true;
            }
        }
        return false;
    }


    void IMenuElement::callEvent(std::string eventName)
    {
        unsigned int pos = std::find(this->eventNames.begin(), this->eventNames.end(), eventName) - this->eventNames.begin();
        if (pos < this->events.size())
            this->events[pos].call();
    }


    void IMenuElement::attachCallback(std::string eventName, MenuCallback callback)
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
}