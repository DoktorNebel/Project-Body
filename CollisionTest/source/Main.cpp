#include "Engine.h"
#include "TestGame.h"

int main()
{
    test::TestGame game;
    se::EngineSettings settings;
    settings.fullscreen = false;
    settings.renderResolutionWidth = 1280;
    settings.renderResolutionHeight = 720;
    settings.screenResolutionWidth = 1280;
    settings.screenResolutionHeight = 720;
    se::Engine::initialize(&game, settings);

    se::Engine::run();
}