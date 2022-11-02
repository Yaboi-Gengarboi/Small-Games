// RPGTest
// InputManager.cpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-11-01 by Justyn Durnford
// Source file for the InputManager class.

#ifndef NOMINMAX
#define NOMINMAX
#endif // #ifndef NOMINMAX

#include "InputManager.hpp"

#include "Mouse.hpp"
using jlib::get_mouse_position;

#include <algorithm>
using std::max;
using std::shift_right;

void InputManager::_updateKeyStates()
{
	for (std::pair<const Keyboard::Key, InputBuffer<u8>>& pair : keyStates)
	{
		if (Keyboard::isKeyPressed(pair.first))
			keyStates[pair.first].update(true);
		else
			keyStates[pair.first].update(false);
	}
}

void InputManager::_updateButtonStates()
{
	for (std::pair<const Gamepad::Button, InputBuffer<u8>>& pair : buttonStates)
	{
		if (controller.isButtonPressed(pair.first))
			buttonStates[pair.first].update(true);
		else
			buttonStates[pair.first].update(false);
	}
}

InputManager::InputManager()
{
	keyStates[Keyboard::Key::W] = 0;
	keyStates[Keyboard::Key::A] = 0;
	keyStates[Keyboard::Key::S] = 0;
	keyStates[Keyboard::Key::D] = 0;
	keyStates[Keyboard::Key::LShift] = 0;
	keyStates[Keyboard::Key::LControl] = 0;
	keyStates[Keyboard::Key::Tab] = 0;
	keyStates[Keyboard::Key::Escape] = 0;
	keyStates[Keyboard::Key::Enter] = 0;

	buttonStates[Gamepad::Button::A] = 0;
	buttonStates[Gamepad::Button::B] = 0;
	buttonStates[Gamepad::Button::X] = 0;
	buttonStates[Gamepad::Button::Y] = 0;
	buttonStates[Gamepad::Button::DPadUp] = 0;
	buttonStates[Gamepad::Button::DPadDown] = 0;
	buttonStates[Gamepad::Button::DPadLeft] = 0;
	buttonStates[Gamepad::Button::DPadRight] = 0;
	buttonStates[Gamepad::Button::LShoulder] = 0;
	buttonStates[Gamepad::Button::RShoulder] = 0;
	buttonStates[Gamepad::Button::LThumbstick] = 0;
	buttonStates[Gamepad::Button::RThumbstick] = 0;
	buttonStates[Gamepad::Button::Start] = 0;
	buttonStates[Gamepad::Button::Back] = 0;
}

void InputManager::setControllerDeadZones(float lx_dz, float ly_dz, float rx_dz, float ry_dz)
{
	controller.leftStick.setDeadzones(lx_dz, ly_dz);
	controller.rightStick.setDeadzones(rx_dz, ry_dz);
}

bool InputManager::getCurrentKeyState(Keyboard::Key key)
{
	return keyStates[key].isActive();
}

u8 InputManager::getKeyState(Keyboard::Key key)
{
	return keyStates[key].getValue();
}

bool InputManager::getCurrentButtonState(Gamepad::Button button)
{
	return buttonStates[button].isActive();
}

u8 InputManager::getButtonState(Gamepad::Button button)
{
	return buttonStates[button].getValue();
}

Ptr<const Direction> InputManager::getCurrentDirection()
{
	if (controller.isConnected())
		return controller.leftStick.getDirection();
	else
	{
		if (getCurrentKeyState(Keyboard::W))
		{
			if (getCurrentKeyState(Keyboard::A))
				return &Direction::Northwest;
			else if (getCurrentKeyState(Keyboard::D))
				return &Direction::Northeast;
			else
				return &Direction::North;
		}
		else if (getCurrentKeyState(Keyboard::S))
		{
			if (getCurrentKeyState(Keyboard::A))
				return &Direction::Southwest;
			else if (getCurrentKeyState(Keyboard::D))
				return &Direction::Southeast;
			else
				return &Direction::South;
		}
		else if (getCurrentKeyState(Keyboard::A))
			return &Direction::West;
		else if (getCurrentKeyState(Keyboard::D))
			return &Direction::East;
	}

	return nullptr;
}

void InputManager::update(Ptr<RenderWindow> window)
{
	if (window->hasFocus())
	{
		controller.update();
		_updateKeyStates();
		_updateButtonStates();
		mousePosition = get_mouse_position(*window);
	}
}