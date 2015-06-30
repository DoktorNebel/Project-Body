#pragma once

#include <string>

namespace se
{
    class IMenuElement;

    class MenuMessage
    {
    public:

        std::string senderName;
        IMenuElement* sender;
        void* data;

        MenuMessage(std::string senderName, IMenuElement* sender, void* data = 0);
        ~MenuMessage();
    };
}