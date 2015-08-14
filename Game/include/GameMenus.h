#pragma once

#include "Engine.h"
#include "MenuEvent.h"

namespace bg
{
    void createMenus();
    void createFunctionality();

    se::MenuCallback startButtonFunction;
    se::MenuCallback highlightFunction;
    se::MenuCallback unhighlightFunction;
    se::MenuCallback highlightFunction2;
    se::MenuCallback unhighlightFunction2;
    se::MenuCallback startGameButtonFunction;
    se::MenuCallback levelButtonFunction;
    se::MenuCallback exitButtonFunction;
    se::MenuCallback uiUpdateFunction;
}