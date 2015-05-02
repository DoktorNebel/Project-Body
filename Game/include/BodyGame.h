#pragma once

#include "IGame.h"
#include "Camera.h"

namespace bg
{
	class BodyGame : public se::IGame
	{
	private:

		std::vector<se::Sprite> sprite;
		se::Camera camera;
		bool pressed;

	public:

		BodyGame();
		~BodyGame();

	public:

		virtual void initialize();
		virtual void update(float elapsedTime);
		virtual void draw();
		virtual void close();
	};
}