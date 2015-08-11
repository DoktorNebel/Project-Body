#include "Engine.h"

#include "IScene.h"
#include "Input.h"


namespace se
{
    bool Engine::running = true;
    IScene* Engine::scene = 0;
    IScene* Engine::newScene = 0;
    sf::Window* Engine::window = 0;
    Graphics Engine::graphics;
    SoundManager Engine::sound;
    std::chrono::time_point<std::chrono::high_resolution_clock> Engine::lastUpdate;
    Camera* Engine::camera = 0;
    Camera Engine::menuCamera = Camera();
    EngineSettings Engine::settings;
    MenuSystem Engine::menuSystem;


    void Engine::initialize(IScene* startScene, void(*createMenusFunction)(), void(*createMenuFunctionalityFunction)(), EngineSettings settings)
    {
        Engine::scene = startScene;
        Engine::window = new sf::Window(sf::VideoMode(settings.screenResolutionWidth, settings.screenResolutionHeight), "Body", settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(24, 0, 2, 3, 3));
        Engine::graphics = Graphics(settings);
        Engine::settings = settings;
        Engine::sound.initialize();

        createMenusFunction();
        Engine::menuSystem.initialize();
        createMenuFunctionalityFunction();

        Engine::window->setActive(true);
        srand((unsigned int)time(0));

        Engine::lastUpdate = std::chrono::high_resolution_clock::now();
        
        Input::setWindow(Engine::window);
    }


	EngineSettings& Engine::getSettings()
	{
		return Engine::settings;
	}


	void Engine::reloadSettings()
	{
        Engine::window->create(sf::VideoMode(Engine::settings.screenResolutionWidth, Engine::settings.screenResolutionHeight), "Body", Engine::settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(24, 0, 2, 4, 3));
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
        Engine::scene->initialize();

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

            Engine::menuSystem.update(elapsedTime);
            Engine::scene->update(elapsedTime);
            Engine::graphics.beginDraw();
            Engine::scene->draw();
            Engine::graphics.draw(Engine::camera);
            Engine::menuSystem.draw();
            Engine::graphics.draw(&Engine::menuCamera);
            Engine::window->display();

            if (Engine::newScene)
            {
                Engine::scene->close();
                delete Engine::scene;
                Engine::scene = Engine::newScene;
                Engine::newScene = 0;
                Engine::scene->initialize();
            }
        }

        Engine::scene->close();

        Engine::window->close();
    }


    void Engine::draw(Sprite& sprite)
    {
        Engine::graphics.addSprite(sprite);
    }


    void Engine::draw(Text& text)
    {
        Engine::graphics.addText(text);
    }


    void Engine::playSound(Sound& sound)
    {
        Engine::sound.playSound(sound);
    }


    void Engine::changeScene(IScene* newScene)
    {
        Engine::newScene = newScene;
    }


    MenuSystem* Engine::getMenu()
    {
        return &Engine::menuSystem;
    }
}