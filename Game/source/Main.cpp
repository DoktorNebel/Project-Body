#include "Engine.h"
#include "BodyGame.h"
#include "GameMenus.h"

int main()
{
    bg::BodyGame* game = new bg::BodyGame();

    bg::createMenus();

	se::EngineSettings settings;
    settings.fullscreen = false;
    settings.renderResolutionWidth = 1280;
    settings.renderResolutionHeight = 720;
	settings.screenResolutionWidth = 1280;
	settings.screenResolutionHeight = 720;
    se::Engine::initialize(game, settings);

    se::Engine::run();

    return 0;
}