#include "MenuMessage.h"

namespace se
{
    MenuMessage::MenuMessage(std::string senderName, IMenuElement* sender, void* data)
        : senderName(senderName)
        , sender(sender)
        , data(data)
    {

    }


    MenuMessage::~MenuMessage()
    {
        if (this->data)
            delete this->data;
    }
}