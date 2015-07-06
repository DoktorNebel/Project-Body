#pragma once

#include "Engine.h"
#include "MenuEvent.h"
#include "Tilesets.h"

namespace be
{
    struct MenuData
    {
        bc::Tileset::Type levelType;
    };

    void createMenus();
    void createFunctionality();

    se::MenuCallback newButtonFunction;
    se::MenuCallback highlightFunction;
    se::MenuCallback unhighlightFunction;
    se::MenuCallback highlightSpriteFunction;
    se::MenuCallback unhighlightSpriteFunction;
    se::MenuCallback backgroundButtonFunction;
}