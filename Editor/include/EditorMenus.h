#pragma once

#include "Engine.h"
#include "MenuEvent.h"
#include "Tilesets.h"

namespace be
{
    class EditorScene;

    struct MenuData
    {
        bc::Tileset::Type levelType;
        std::string currentTile;
        EditorScene* scene;
    };

    void createMenus();
    void createFunctionality();

    se::MenuCallback newButtonFunction;
    se::MenuCallback highlightFunction;
    se::MenuCallback unhighlightFunction;
    se::MenuCallback highlightSpriteFunction;
    se::MenuCallback unhighlightSpriteFunction;
    se::MenuCallback backgroundButtonFunction;
    se::MenuCallback tileButtonFunction;
	se::MenuCallback saveButtonFunction;
	se::MenuCallback loadButtonFunction;
}