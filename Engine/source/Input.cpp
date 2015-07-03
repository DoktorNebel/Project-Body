#include "Input.h"

#include "Engine.h"

namespace se
{
	sf::Window* Input::window = 0;
	std::vector<Input::InputAction> Input::inputActions = std::vector<Input::InputAction>();
	std::vector<float> Input::previousValues = std::vector<float>();


    void Input::bindMouseButtonAction(unsigned int action, sf::Mouse::Button mouseButton, bool alternative)
	{
		if (Input::inputActions.size() <= action)
        {
            Input::InputAction inputAction;
            inputAction.inputType = alternative ? Input::InputType::Unbound : Input::InputType::Mouse;
            inputAction.alternativeInputType = alternative ? Input::InputType::Mouse : Input::InputType::Unbound;
            inputAction.index = 0;
            inputAction.alternativeIndex = 0;
            inputAction.action = action;
            inputAction.input = mouseButton;
            inputAction.alternativeInput = mouseButton;
            inputAction.positive = true;
            inputAction.alternativePositive = true;
            inputAction.value = 0.0f;
            inputAction.pressed = false;
            inputAction.released = false;

			Input::inputActions.resize(action + 1);
			Input::previousValues.resize(action + 1);

		    Input::inputActions[action] = inputAction;
		}
        else
        {
            if (alternative)
            {
                Input::inputActions[action].alternativeInputType = Input::InputType::Mouse;
                Input::inputActions[action].alternativeInput = mouseButton;
            }
            else
            {
                Input::inputActions[action].inputType = Input::InputType::Mouse;
                Input::inputActions[action].input = mouseButton;
            }
        }
	}


    void Input::bindKeyboardKeyAction(unsigned int action, sf::Keyboard::Key keyboardKey, bool alternative)
    {
        if (Input::inputActions.size() <= action)
        {
            Input::InputAction inputAction;
            inputAction.inputType = alternative ? Input::InputType::Unbound : Input::InputType::Keyboard;
            inputAction.alternativeInputType = alternative ? Input::InputType::Keyboard : Input::InputType::Unbound;
            inputAction.index = 0;
            inputAction.alternativeIndex = 0;
            inputAction.action = action;
            inputAction.input = keyboardKey;
            inputAction.alternativeInput = keyboardKey;
            inputAction.positive = true;
            inputAction.alternativePositive = true;
            inputAction.value = 0.0f;
            inputAction.pressed = false;
            inputAction.released = false;

            Input::inputActions.resize(action + 1);
            Input::previousValues.resize(action + 1);

            Input::inputActions[action] = inputAction;
        }
        else
        {
            if (alternative)
            {
                Input::inputActions[action].alternativeInputType = Input::InputType::Keyboard;
                Input::inputActions[action].alternativeInput = keyboardKey;
            }
            else
            {
                Input::inputActions[action].inputType = Input::InputType::Keyboard;
                Input::inputActions[action].input = keyboardKey;
            }
        }
	}


    void Input::bindJoystickButtonAction(unsigned int action, unsigned int joystickIndex, unsigned int button, bool alternative)
    {
        if (Input::inputActions.size() <= action)
        {
            Input::InputAction inputAction;
            inputAction.inputType = alternative ? Input::InputType::Unbound : Input::InputType::JoystickButton;
            inputAction.alternativeInputType = alternative ? Input::InputType::JoystickButton : Input::InputType::Unbound;
            inputAction.index = joystickIndex;
            inputAction.alternativeIndex = joystickIndex;
            inputAction.action = action;
            inputAction.input = button;
            inputAction.alternativeInput = button;
            inputAction.positive = true;
            inputAction.alternativePositive = true;
            inputAction.value = 0.0f;
            inputAction.pressed = false;
            inputAction.released = false;

            Input::inputActions.resize(action + 1);
            Input::previousValues.resize(action + 1);

            Input::inputActions[action] = inputAction;
        }
        else
        {
            if (alternative)
            {
                Input::inputActions[action].alternativeInputType = Input::InputType::JoystickButton;
                Input::inputActions[action].alternativeIndex = joystickIndex;
                Input::inputActions[action].alternativeInput = button;
            }
            else
            {
                Input::inputActions[action].inputType = Input::InputType::JoystickButton;
                Input::inputActions[action].index = joystickIndex;
                Input::inputActions[action].input = button;
            }
        }
	}


    void Input::bindJoystickAxisAction(unsigned int action, unsigned int joystickIndex, unsigned int axis, bool positive, bool alternative)
    {
        if (Input::inputActions.size() <= action)
        {
            Input::InputAction inputAction;
            inputAction.inputType = alternative ? Input::InputType::Unbound : Input::InputType::JoystickButton;
            inputAction.alternativeInputType = alternative ? Input::InputType::JoystickButton : Input::InputType::Unbound;
            inputAction.index = joystickIndex;
            inputAction.alternativeIndex = joystickIndex;
            inputAction.action = action;
            inputAction.input = axis;
            inputAction.alternativeInput = axis;
            inputAction.positive = positive;
            inputAction.alternativePositive = positive;
            inputAction.value = 0.0f;
            inputAction.pressed = false;
            inputAction.released = false;

            Input::inputActions.resize(action + 1);
            Input::previousValues.resize(action + 1);

            Input::inputActions[action] = inputAction;
        }
        else
        {
            if (alternative)
            {
                Input::inputActions[action].alternativeInputType = Input::InputType::JoystickButton;
                Input::inputActions[action].alternativeIndex = joystickIndex;
                Input::inputActions[action].alternativeInput = axis;
                Input::inputActions[action].alternativePositive = positive;
            }
            else
            {
                Input::inputActions[action].inputType = Input::InputType::JoystickButton;
                Input::inputActions[action].index = joystickIndex;
                Input::inputActions[action].input = axis;
                Input::inputActions[action].positive = positive;
            }
        }
	}


    void Input::unbindAction(unsigned int action, bool alternative)
	{
        if (alternative)
            Input::inputActions[action].alternativeInputType = Input::InputType::Unbound;
        else
    		Input::inputActions[action].inputType = Input::InputType::Unbound;
	}


	Vector2 Input::getMousePos()
	{
        return Vector2(sf::Mouse::getPosition(*Input::window).x - (int)Engine::getSettings().renderResolutionWidth / 2, (sf::Mouse::getPosition(*Input::window).y - (int)Engine::getSettings().renderResolutionHeight / 2) * -1);
	}


    bool Input::actionPressed(unsigned int action)
	{
        if (Input::inputActions[action].pressed)
        {
            Input::inputActions[action].pressed = false;
            return true;
        }
        return false;
		//return Input::inputActions[action].pressed;
	}


    bool Input::actionReleased(unsigned int action)
	{
		return Input::inputActions[action].released;
	}


    float Input::getActionValue(unsigned int action)
	{
		return Input::inputActions[action].value;
	}


	void Input::setWindow(sf::Window* window)
	{
		Input::window = window;
	}


	void Input::update()
	{
		for (unsigned int i = 0; i < Input::inputActions.size(); ++i)
		{
			InputAction& action = Input::inputActions[i];

            //check primary bindings
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


            //check alternative bindings
            switch (action.alternativeInputType)
            {
            case Input::InputType::Mouse:
                action.value = sf::Mouse::isButtonPressed((sf::Mouse::Button)action.alternativeInput);
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
                action.value = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)action.alternativeInput);
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
                action.value = sf::Joystick::isButtonPressed(action.alternativeIndex, action.alternativeInput);
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
                action.value = sf::Joystick::getAxisPosition(action.alternativeIndex, (sf::Joystick::Axis)action.alternativeInput) / 100.0f;
                if (action.alternativePositive)
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