#pragma once

#include "SFML\Window.hpp"
#include "Vector2.h"

namespace se
{
	class Input
	{
	private:

		struct InputType
		{
			enum Type
			{
				Unbound,
				Mouse,
				Keyboard,
				JoystickButton,
				JoystickAxis
			};
		};

		struct InputAction
		{
            InputType::Type inputType;
            InputType::Type alternativeInputType;
            unsigned int index;
            unsigned int alternativeIndex;
            unsigned int action;
            unsigned int input;
            unsigned int alternativeInput;
            bool positive;
            bool alternativePositive;
			float value;
			bool pressed;
			bool released;
		};

	private:

		static sf::Window* window;
		static std::vector<InputAction> inputActions;
		static std::vector<float> previousValues;

	private:

		Input();

	public:

        static void bindMouseButtonAction(unsigned int action, sf::Mouse::Button mouseButton, bool alternative = false);
        static void bindKeyboardKeyAction(unsigned int action, sf::Keyboard::Key keyboardKey, bool alternative = false);
        static void bindJoystickButtonAction(unsigned int action, unsigned int joystickIndex, unsigned int button, bool alternative = false);
        static void bindJoystickAxisAction(unsigned int action, unsigned int joystickIndex, unsigned int axis, bool positive, bool alternative = false);
        static void unbindAction(unsigned int action, bool alternative = false);
		static Vector2 getMousePos();
        static bool actionPressed(unsigned int action);
        static bool actionReleased(unsigned int action);
        static float getActionValue(unsigned int action);
		static void setWindow(sf::Window* window);
		static void update();
	};
}