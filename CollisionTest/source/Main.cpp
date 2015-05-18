#include "Engine.h"
#include "TestGame.h"

int main()
{
    test::TestGame game;
    se::EngineSettings settings;
    settings.fullscreen = false;
    settings.resolutionWidth = 1280;
    settings.resolutionHeight = 720;
    se::Engine::initialize(&game, settings);

    se::Engine::run();
}