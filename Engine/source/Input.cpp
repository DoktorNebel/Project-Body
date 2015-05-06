#include "Input.h"

namespace se
{
	sf::Window* Input::window = 0;
	std::vector<Input::InputAction> Input::inputActions = std::vector<Input::InputAction>();
	std::vector<float> Input::previousValues = std::vector<float>();


	void Input::bindMouseButtonAction(int action, sf::Mouse::Button mouseButton)
	{
		Input::InputAction inputAction;
		inputAction.inputType = Input::InputType::Mouse;
		inputAction.index = 0;
		inputAction.action = action;
		inputAction.input = mouseButton;
		inputAction.positive = true;
		inputAction.value = 0.0f;
		inputAction.pressed = false;
		inputAction.released = false;

		if (Input::inputActions.size() <= action)
		{
			Input::inputActions.resize(action + 1);
			Input::previousValues.resize(action + 1);
		}

		Input::inputActions[action] = inputAction;
	}


	void Input::bindKeyboardKeyAction(int action, sf::Keyboard::Key keyboardKey)
	{
		Input::InputAction inputAction;
		inputAction.inputType = Input::InputType::Keyboard;
		inputAction.index = 0;
		inputAction.action = action;
		inputAction.input = keyboardKey;
		inputAction.positive = true;
		inputAction.value = 0.0f;
		inputAction.pressed = false;
		inputAction.released = false;

		if (Input::inputActions.size() <= action)
		{
			Input::inputActions.resize(action + 1);
			Input::previousValues.resize(action + 1);
		}

		Input::inputActions[action] = inputAction;
	}


	void Input::bindJoystickButtonAction(int action, unsigned int joystickIndex, unsigned int button)
	{
		Input::InputAction inputAction;
		inputAction.inputType = Input::InputType::JoystickButton;
		inputAction.index = joystickIndex;
		inputAction.action = action;
		inputAction.input = button;
		inputAction.positive = true;
		inputAction.value = 0.0f;
		inputAction.pressed = false;
		inputAction.released = false;

		if (Input::inputActions.size() <= action)
		{
			Input::inputActions.resize(action + 1);
			Input::previousValues.resize(action + 1);
		}

		Input::inputActions[action] = inputAction;
	}


	void Input::bindJoystickAxisAction(int action, unsigned int joystickIndex, unsigned int axis, bool positive)
	{
		Input::InputAction inputAction;
		inputAction.inputType = Input::InputType::JoystickAxis;
		inputAction.index = joystickIndex;
		inputAction.action = action;
		inputAction.input = axis;
		inputAction.positive = positive;
		inputAction.value = 0.0f;
		inputAction.pressed = false;
		inputAction.released = false;

		if (Input::inputActions.size() <= action)
		{
			Input::inputActions.resize(action + 1);
			Input::previousValues.resize(action + 1);
		}

		Input::inputActions[action] = inputAction;
	}


	void Input::unbindAction(int action)
	{
		Input::inputActions[action].inputType = Input::InputType::Unbound;
	}


	Vector2 Input::getMousePos()
	{
		return *(Vector2*)&sf::Mouse::getPosition(*Input::window);
	}


	bool Input::actionPressed(int action)
	{
		return Input::inputActions[action].pressed;
	}


	bool Input::actionReleased(int action)
	{
		return Input::inputActions[action].released;
	}


	float Input::getActionValue(int action)
	{
		return Input::inputActions[action].value;
	}


	void Input::setWindow(sf::Window* window)
	{
		Input::window = window;
	}


	void Input::update()
	{
		for (int i = 0; i < Input::inputActions.size(); ++i)
		{
			InputAction& action = Input::inputActions[i];

			switch (action.inputType)
			{
			case Input::InputType::Mouse:
				action.value = sf::Mouse::isButtonPressed((sf::Mouse::Button)action.input);
				if (Input::previousValues[i] != action.value)
				{
					if (action.value == 1.0f)
						action.pressed = true;
					else
						action.released = true;
				}
				else
				{
					action.pressed = false;
					action.released = false;
				}
				Input::previousValues[i] = action.value;
				break;


			case Input::InputType::Keyboard:
				action.value = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)action.input);
				if (Input::previousValues[i] != action.value)
				{
					if (action.value == 1.0f)
						action.pressed = true;
					else
						action.released = true;
				}
				else
				{
					action.pressed = false;
					action.released = false;
				}
				Input::previousValues[i] = action.value;
				break;


			case Input::InputType::JoystickButton:
				action.value = sf::Joystick::isButtonPressed(action.index, action.input);
				if (Input::previousValues[i] != action.value)
				{
					if (action.value == 1.0f)
						action.pressed = true;
					else
						action.released = true;
				}
				else
				{
					action.pressed = false;
					action.released = false;
				}
				Input::previousValues[i] = action.value;
				break;


			case Input::InputType::JoystickAxis:
				action.value = sf::Joystick::getAxisPosition(action.index, (sf::Joystick::Axis)action.input) / 100.0f;
				if (action.positive)
					action.value = action.value < 0.0f ? 0.0f : action.value;
				else
					action.value = action.value > 0.0f ? 0.0f : action.value;
				if (Input::previousValues[i] != action.value)
				{
					if (action.value > 0.0f)
						action.pressed = true;
					else
						action.released = true;
				}
				else
				{
					action.pressed = false;
					action.released = false;
				}
				Input::previousValues[i] = action.value;
				break;
			}
		}
	}
}