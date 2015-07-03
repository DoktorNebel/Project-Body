#include "MenuSystem.h"

namespace se
{
    void MenuSystem::initialize()
    {
        this->show();
        for (unsigned int i = 0; i < this->menus.size(); ++i)
        {
            this->menus[i].initialize(this);
        }
        
    }


    void MenuSystem::update(float elapsedTime)
    {
        if (this->visible)
            this->currentMenu->update(elapsedTime);
    }


    void MenuSystem::draw()
    {
        if (this->visible)
            this->currentMenu->draw();
    }


    void MenuSystem::addMenu(std::string name)
    {
        this->menuNames.push_back(name);
        this->menus.push_back(Menu());
    }


    void MenuSystem::addElement(std::string menuName, std::string name, IMenuElement* element)
    {
        unsigned int pos = std::find(this->menuNames.begin(), this->menuNames.end(), menuName) - this->menuNames.begin();
        if (pos < this->menus.size())
            this->menus[pos].addElement(name, element);
    }


    void MenuSystem::attachCallback(std::string menuName, std::string elementName, std::string eventName, MenuCallback* callback)
    {
        unsigned int pos = std::find(this->menuNames.begin(), this->menuNames.end(), menuName) - this->menuNames.begin();
        if (pos < this->menus.size())
            this->menus[pos].attachCallback(elementName, eventName, callback);
    }


    void MenuSystem::changeMenu(std::string menuName)
    {
        unsigned int pos = std::find(this->menuNames.begin(), this->menuNames.end(), menuName) - this->menuNames.begin();
        if (pos < this->menus.size())
            this->currentMenu = &this->menus[pos];

        if (this->currentMenu->getElement(0))
            this->highlight(this->currentMenu->getElement(0));
    }


    IMenuElement* MenuSystem::getElement(std::string menuName, std::string elementName)
    {
        unsigned int pos = std::find(this->menuNames.begin(), this->menuNames.end(), menuName) - this->menuNames.begin();
        if (pos < this->menus.size())
            return this->menus[pos].getElement(elementName);

        return 0;
    }


    void MenuSystem::show()
    {
        this->visible = true;
    }


    void MenuSystem::hide()
    {
        this->visible = false;
    }


    void MenuSystem::highlight(IMenuElement* element)
    {
        if (this->highlightedElement)
            this->highlightedElement->unhighlight();
        this->highlightedElement = element;
        this->highlightedElement->highlight();
    }
}