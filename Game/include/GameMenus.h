#pragma once

#include "Engine.h"
#include "MenuEvent.h"

namespace bg
{
    void createMenus();
    void createFunctionality();

    se::MenuCallback highlightFunction;
    se::MenuCallback unhighlightFunction;
    se::MenuCallback highlightFunction2;
    se::MenuCallback unhighlightFunction2;

    se::MenuCallback startButtonFunction;
    se::MenuCallback startGameButtonFunction;
    se::MenuCallback levelButtonFunction;
    se::MenuCallback exitButtonFunction;
    se::MenuCallback resumeButtonFunction;
    se::MenuCallback restartButtonFunction;
    se::MenuCallback mainMenuButtonFunction;
    se::MenuCallback highscoreButtonFunction;
    se::MenuCallback backButtonFunction;
    se::MenuCallback nextLevelButtonFunction;
    se::MenuCallback characterButtonFunction;
    se::MenuCallback changeBackgroundFunction;
    se::MenuCallback saveScoreFunction;
    se::MenuCallback changeControlsFunction;
    se::MenuCallback optionsButtonFunction;

    se::MenuCallback uiUpdateFunction;
}