#include "Menu.h"

namespace se
{
    Menu::Menu()
    {

    }


    Menu::~Menu()
    {

    }


    void Menu::initialize(MenuSystem* menuSystem)
    {
        if (this->elements.size() > 0)
        {
            this->elements[0]->doInitialize(menuSystem, true);
            for (unsigned int i = 1; i < this->elements.size(); ++i)
            {
                this->elements[i]->doInitialize(menuSystem, false);
            }
        }
    }


    void Menu::update(float elapsedTime)
    {
        for (unsigned int i = 0; i < this->elements.size(); ++i)
        {
            this->elements[i]->doUpdate(elapsedTime);
        }
    }


    void Menu::draw()
    {
        for (unsigned int i = 0; i < this->elements.size(); ++i)
        {
            this->elements[i]->doDraw();
        }
    }


    void Menu::attachCallback(std::string elementName, std::string eventName, MenuCallback* callback)
    {
        unsigned int pos = std::find(this->elementNames.begin(), this->elementNames.end(), elementName) - this->elementNames.begin();
        if (pos < this->elements.size())
            this->elements[pos]->attachCallback(eventName, callback);
    }


    void Menu::addElement(std::string name, IMenuElement* element)
    {
        this->elementNames.push_back(name);
        this->elements.push_back(element);
    }


    IMenuElement* Menu::getElement(unsigned int index)
    {
        return this->elements[index];
    }


    IMenuElement* Menu::getElement(std::string elementName)
    {
        unsigned int pos = std::find(this->elementNames.begin(), this->elementNames.end(), elementName) - this->elementNames.begin();
        if (pos < this->elements.size())
            return this->elements[pos];

        return 0;
    }
}