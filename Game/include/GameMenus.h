#pragma once

#include "Engine.h"
#include "MenuEvent.h"

namespace bg
{
    struct MenuData
    {
        std::string levelName;
    };


    void createMenus();
    void createFunctionality();

    se::MenuCallback startButtonFunction;
    se::MenuCallback highlightFunction;
    se::MenuCallback unhighlightFunction;
    se::MenuCallback highlightFunction2;
    se::MenuCallback unhighlightFunction2;
    se::MenuCallback startGameButtonFunction;
    se::MenuCallback levelButtonFunction;
}