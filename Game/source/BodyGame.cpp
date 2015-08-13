#include "BodyGame.h"

#include "MathFunctions.h"
#include "Content.h"
#include "GameMenus.h"

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