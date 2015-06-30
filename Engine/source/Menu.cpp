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


    void Menu::addElement(std::string name, IMenuElement* element)
    {
        this->elementNames.push_back(name);
        this->elements.push_back(element);
    }


    std::vector<Sprite> Menu::getSprites()
    {
        std::vector<Sprite> result;
        for (unsigned int i = 0; i < this->elements.size(); ++i)
        {
            result.insert(result.end(), this->elements[i]->getSprites().begin(), this->elements[i]->getSprites().end());
        }
        return result;
    }


    std::vector<Text> Menu::getTexts()
    {
        std::vector<Text> result;
        for (unsigned int i = 0; i < this->elements.size(); ++i)
        {
            result.insert(result.end(), this->elements[i]->getTexts().begin(), this->elements[i]->getTexts().end());
        }
        return result;
    }


    std::vector<MenuMessage> Menu::getMessages()
    {
        std::vector<MenuMessage> result;
        for (unsigned int i = 0; i < this->elements.size(); ++i)
        {
            result.insert(result.end(), this->elements[i]->getMessages().begin(), this->elements[i]->getMessages().end());
        }
        return result;
    }
}