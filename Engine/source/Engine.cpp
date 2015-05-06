#include "Engine.h"

#include "IGame.h"
#include "Input.h"


namespace se
{
    bool Engine::running = true;
    IGame* Engine::game = 0;
    sf::Window* Engine::window = 0;
    Graphics Engine::graphics;
    std::chrono::system_clock::time_point Engine::lastUpdate;
    Camera* Engine::camera = 0;
    EngineSettings Engine::settings;


    void Engine::initialize(IGame* game, EngineSettings settings)
    {
        Engine::game = game;
        Engine::window = new sf::Window(sf::VideoMode(settings.resolutionWidth, settings.resolutionHeight), "Body", settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(24, 0, 2, 4, 3));
        Engine::graphics = Graphics(settings);
        Engine::settings = settings;

        Engine::window->setActive(true);
        srand(time(0));

        Engine::lastUpdate = std::chrono::high_resolution_clock::now();

        Input::setWindow(Engine::window);
    }


	EngineSettings& Engine::getSettings()
	{
		return Engine::settings;
	}


	void Engine::reloadSettings()
	{
		Engine::window->create(sf::VideoMode(Engine::settings.resolutionWidth, Engine::settings.resolutionHeight), "Body", Engine::settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(24, 0, 2, 4, 3));
	}


    Camera& Engine::getActiveCamera()
    {
        return *Engine::camera;
    }


    void Engine::setActiveCamera(Camera& camera)
    {
        Engine::camera = &camera;
    }


    void Engine::run()
    {
        Engine::game->initialize();

        while (Engine::running)
        {
            sf::Event message;
            while (Engine::window->pollEvent(message))
            {
                switch (message.type)
                {
                case sf::Event::Closed:
                    Engine::running = false;
                    break;
                }
            }

			Input::update();

            std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = now - Engine::lastUpdate;
            float elapsedTime = elapsed.count();
            Engine::lastUpdate = now;

            Engine::game->update(elapsedTime);
            Engine::game->draw();
            Engine::graphics.draw(Engine::camera);
            Engine::window->display();
        }

        Engine::game->close();

        Engine::window->close();
    }


    void Engine::draw(Sprite& sprite)
    {
        Engine::graphics.addSprite(sprite);
    }
}