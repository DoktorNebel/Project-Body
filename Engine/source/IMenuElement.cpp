#include "IMenuElement.h"

namespace se
{
    void IMenuElement::attachCallback(std::string eventName, MenuCallback callback)
    {
        unsigned int pos = std::find(this->eventNames.begin(), this->eventNames.end(), eventName) - this->eventNames.begin();
        if (pos < this->events.size())
            this->events[pos].callbacks.push_back(callback);
    }
}