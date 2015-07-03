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
}