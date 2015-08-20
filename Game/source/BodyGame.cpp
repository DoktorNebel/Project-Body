#include "BodyGame.h"

#include "MathFunctions.h"
#include "Content.h"
#include "GameMenus.h"
#include "MenuData.h"
#include "Input.h"
#include "Engine.h"
#include "InputActions.h"

namespace bg
{
	BodyGame::BodyGame()
	{
        
	}


	BodyGame::~BodyGame()
	{

	}


	void BodyGame::initialize()
    {
        this->level.initialize(((MenuData*)se::Engine::getMenu()->data)->levelName);

        this->music = se::Content::getSound("first_flight");
        this->musicLoop = se::Content::getSound("first_flight_loop");
        this->musicLoop.setLooping(true);
        se::Engine::playSound(this->music);

        this->paused = false;

        this->musicTimer = 59.0f;
        this->loopPlaying = false;
	}


	void BodyGame::update(float elapsedTime)
	{
        if (!this->paused)
            this->level.update(elapsedTime);

        if (se::Input::actionPressed(InputAction::Pause))
        {
            if (this->paused)
                this->resume();
            else
                this->pause();
        }

        this->musicTimer -= elapsedTime;
        if (this->musicTimer <= 0.0f && !this->loopPlaying)
        {
            this->loopPlaying = true;
            se::Engine::playSound(this->musicLoop);
        }
	}


	void BodyGame::draw()
	{
        this->level.draw();
	}


	void BodyGame::close()
    {
        se::Engine::stopSound(this->music);
        se::Engine::stopSound(this->musicLoop);
	}


    void BodyGame::pause()
    {
        se::Engine::getMenu()->changeMenu("Pause");
        this->paused = true;
    }


    void BodyGame::resume()
    {
        se::Engine::getMenu()->changeMenu("UI");
        this->paused = false;
    }


    void BodyGame::restartLevel()
    {
        this->level.initialize(((MenuData*)se::Engine::getMenu()->data)->levelName);
    }
}