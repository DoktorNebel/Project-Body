#include "Menu.h"

namespace se
{
    Menu::Menu()
    {

    }


    Menu::~Menu()
    {

    }


    void Menu::update(float elapsedTime)
    {
        for (unsigned int i = 0; i < this->elements.size(); ++i)
        {
            this->elements[i]->update(elapsedTime);
        }
    }


    void Menu::draw()
    {
        for (unsigned int i = 0; i < this->elements.size(); ++i)
        {
            this->elements[i]->draw();
        }
    }


    void Menu::attachCallback(std::string elementName, std::string eventName, MenuCallback callback)
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
}