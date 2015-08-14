#include "BodyGame.h"

#include "MathFunctions.h"
#include "Content.h"
#include "GameMenus.h"
#include "MenuData.h"

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
        this->music.setLooping(true);
        se::Engine::playSound(this->music);
	}


	void BodyGame::update(float elapsedTime)
	{
        this->level.update(elapsedTime);
	}


	void BodyGame::draw()
	{
        this->level.draw();
	}


	void BodyGame::close()
	{

	}
}