#pragma once

#include <vector>

namespace se
{
    class IMenuElement;
    class MenuSystem;

    typedef void MenuCallback (IMenuElement* sender, MenuSystem* menuSystem);

    class MenuEvent
    {
    private:

        IMenuElement* owner;
        MenuSystem* menuSystem;

    public:

        std::vector<MenuCallback*> callbacks;

    public:

        MenuEvent(IMenuElement* owner, MenuSystem* menuSystem);

    public:

        void call();
    };
}