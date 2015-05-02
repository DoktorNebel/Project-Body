#pragma once

#include "Graphics.h"
#include <SFML\Window.hpp>
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

        bool running;
        IGame& game;
        sf::Window window;
        Graphics graphics;
        std::chrono::system_clock::time_point lastUpdate;
        Camera* camera;
		EngineSettings settings;

    public:

        Engine(IGame& game, EngineSettings settings);
        ~Engine();

    public:

		EngineSettings& getSettings();
		void reloadSettings();
        void setActiveCamera(Camera& camera);
        void run();
        void draw(Sprite& sprite);
    };
}

