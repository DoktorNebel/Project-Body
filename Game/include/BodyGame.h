#pragma once

#include "IScene.h"
#include "Camera.h"
#include "Level.h"
#include "Sound.h"

namespace bg
{
    class BodyGame : public se::IScene
	{
	private:

        bc::Level level;
        se::Sound music;

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