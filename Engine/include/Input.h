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
			unsigned int index;
			int action;
			unsigned int input;
			bool positive;
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

		static void bindMouseButtonAction(int action, sf::Mouse::Button mouseButton);
		static void bindKeyboardKeyAction(int action, sf::Keyboard::Key keyboardKey);
		static void bindJoystickButtonAction(int action, unsigned int joystickIndex, unsigned int button);
		static void bindJoystickAxisAction(int action, unsigned int joystickIndex, unsigned int axis, bool positive);
		static void unbindAction(int action);
		static Vector2 getMousePos();
		static bool actionPressed(int action);
		static bool actionReleased(int action);
		static float getActionValue(int action);
		static void setWindow(sf::Window* window);
		static void update();
	};
}