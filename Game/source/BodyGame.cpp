#include "BodyGame.h"

#include "MathFunctions.h"
#include "Input.h"
#include "Content.h"
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
		this->engine->setActiveCamera(this->camera);

		for (int i = 0; i < 1000; ++i)
		{
			std::string spriteName = rand() % 2 ? "StaminaBar" : "Testicon";
			this->sprite.push_back(se::Content::getSprite(spriteName));
			this->sprite[i].setPosition(se::Vector2(rand() % 801 - 400, rand() % 601 - 300));
			this->sprite[i].setRotation((float)(rand() & 360));
			this->sprite[i].setDepth((spriteName == "StaminaBar") * -1.0f);
			this->sprite[i].setScale(se::Vector2(0.2f, 0.2f));
		}

		se::Input::bindKeyboardKeyAction(InputActions::Screenshake, sf::Keyboard::Space);
	}


	void BodyGame::update(float elapsedTime)
	{
		if (se::Input::actionPressed(InputActions::Screenshake))
		{
			this->camera.addScreenshake(5, 0.3f);
			this->pressed = true;
		}

		this->camera.update(elapsedTime);

		for (int i = 0; i < this->sprite.size(); ++i)
		{
			this->sprite[i].move(se::Vector2((rand() % 11) - 5, (rand() % 11) - 5) * se::Vector2(elapsedTime * 10.0f, elapsedTime * 10.0f));
			this->sprite[i].rotate((rand() % 11) * elapsedTime);
		}
	}


	void BodyGame::draw()
	{
		for (int i = 0; i < this->sprite.size(); ++i)
		{
			engine->draw(this->sprite[i]);
		}
	}


	void BodyGame::close()
	{

	}
}