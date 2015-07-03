#include "BodyGame.h"

#include "MathFunctions.h"
#include "Content.h"

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
        this->level.initialize("Test");
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