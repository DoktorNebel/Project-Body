#pragma once

#include "Graphics.h"
#include "SFML\Window.hpp"
#include "Content.h"
#include "Sprite.h"
#include <chrono>
#include "Camera.h"
#include "EngineSettings.h"

namespace se
{
    class IGame;


    class Engine
    {
    private:

        static bool running;
        static IGame* game;
        static sf::Window* window;
        static Graphics graphics;
        static std::chrono::system_clock::time_point lastUpdate;
        static Camera* camera;
		static EngineSettings settings;

    public:

        static void initialize(IGame* game, EngineSettings settings);
		static EngineSettings& getSettings();
        static void reloadSettings();
        static Camera& getActiveCamera();
        static void setActiveCamera(Camera& camera);
        static void run();
        static void draw(Sprite& sprite);
        static void draw(Text& text);
    };
}

