#pragma once

#include "Graphics.h"
#include "SFML\Window.hpp"
#include "Content.h"
#include "Sprite.h"
#include <chrono>
#include "Camera.h"
#include "EngineSettings.h"
#include "MenuSystem.h"
#include "SoundManager.h"
#include "Sound.h"

namespace se
{
    class IScene;


    class Engine
    {
    private:

        static bool running;
        static IScene* scene;
        static IScene* newScene;
        static sf::Window* window;
        static Graphics graphics;
        static SoundManager sound;
        static std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdate;
        static Camera* camera;
        static Camera menuCamera;
		static EngineSettings settings;
        static MenuSystem menuSystem;

    public:

        static void initialize(IScene* startScene, void(*createMenusFunction)(), void(*createMenuFunctionalityFunction)(), EngineSettings settings);
		static EngineSettings& getSettings();
        static void reloadSettings();
        static Camera& getActiveCamera();
        static void setActiveCamera(Camera& camera);
        static void run();
        static void draw(Sprite& sprite);
        static void draw(Text& text);
        static void playSound(Sound& sound);
        static void stopSound(Sound& sound);
        static void changeScene(IScene* newScene);
        static IScene* getCurrentScene();
        static MenuSystem* getMenu();
        static void close();
    };
}

