#include "Engine.h"

#include "IGame.h"
#include "Input.h"


namespace se
{
	Engine::Engine(IGame& game, EngineSettings settings)
		: running(true)
		, game(game)
		, window(sf::VideoMode(settings.resolutionWidth, settings.resolutionHeight), "Body", settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(24, 0, 2, 4, 3))
        , graphics(settings)
        , camera(0)
		, settings(settings)
    {
        this->game.engine = this;
        this->window.setActive(true);
        srand(time(0));

        this->lastUpdate = std::chrono::high_resolution_clock::now();

		Input::setWindow(this->window);
    }


    Engine::~Engine()
    {
    }


	EngineSettings& Engine::getSettings()
	{
		return this->settings;
	}


	void Engine::reloadSettings()
	{
		this->window.create(sf::VideoMode(this->settings.resolutionWidth, this->settings.resolutionHeight), "Body", this->settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(24, 0, 2, 4, 3));
	}


    void Engine::setActiveCamera(Camera& camera)
    {
        this->camera = &camera;
    }


    void Engine::run()
    {
        this->game.initialize();

        while (this->running)
        {
            sf::Event message;
            while (this->window.pollEvent(message))
            {
                switch (message.type)
                {
                case sf::Event::Closed:
                    this->running = false;
                    break;
                }
            }

			Input::update();

            std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = now - this->lastUpdate;
            float elapsedTime = elapsed.count();
            this->lastUpdate = now;

            this->game.update(elapsedTime);
            this->game.draw();
            this->graphics.draw(this->camera);
            this->window.display();
        }

        this->game.close();

        this->window.close();
    }


    void Engine::draw(Sprite& sprite)
    {
        this->graphics.addSprite(sprite);
    }
}