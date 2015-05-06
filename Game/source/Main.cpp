#include "Engine.h"
#include "BodyGame.h"

int main()
{
    bg::BodyGame game;
	se::EngineSettings settings;
	settings.fullscreen = false;
	settings.resolutionWidth = 1280;
	settings.resolutionHeight = 720;
    se::Engine::initialize(&game, settings);

    se::Engine::run();

    return 0;
}