// RPGTest
// InputManager.cpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Source file for the InputManager class.

#ifndef NOMINMAX
#define NOMINMAX
#endif // #ifndef NOMINMAX

#include "InputManager.hpp"
#include "Resources.hpp"

void InputManager::_updateKeyStates()
{
	for (std::pair<const Keyboard::Key, InputBuffer>& pair : keyStates)
	{
		if (Keyboard::isKeyPressed(pair.first))
			keyStates[pair.first].update(true);
		else
			keyStates[pair.first].update(false);
	}
}

void InputManager::_updateButtonStates()
{
	for (std::pair<const Gamepad::Button, InputBuffer>& pair : buttonStates)
	{
		if (controller.isButtonPressed(pair.first))
			buttonStates[pair.first].update(true);
		else
			buttonStates[pair.first].update(false);
	}
}

InputManager::InputManager()
{
	reset();
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

u16 InputManager::getKeyState(Keyboard::Key key)
{
	return keyStates[key].getValue();
}

bool InputManager::getCurrentButtonState(Gamepad::Button button)
{
	return buttonStates[button].isActive();
}

u16 InputManager::getButtonState(Gamepad::Button button)
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

void InputManager::sleepFor(Duration secs)
{
	sleepStart = resources->main_clock.getCurrentTimePoint();
	sleepTime = secs;
}

void InputManager::update(RenderWindow& window)
{
	if (window.hasFocus())
	{
		if ((resources->main_clock.getCurrentTimePoint() - sleepStart) >= sleepTime)
		{
			controller.update();
			_updateKeyStates();
			_updateButtonStates();
			mousePosition = window.mapPixelToCoords(Mouse::getPosition(window), window.getView());
		}
	}
}

void InputManager::reset()
{
	keyStates[Keyboard::Key::W].setValue(0);
	keyStates[Keyboard::Key::A].setValue(0);
	keyStates[Keyboard::Key::S].setValue(0);
	keyStates[Keyboard::Key::D].setValue(0);
	keyStates[Keyboard::Key::LShift].setValue(0);
	keyStates[Keyboard::Key::LControl].setValue(0);
	keyStates[Keyboard::Key::Tab].setValue(0);
	keyStates[Keyboard::Key::Escape].setValue(0);
	keyStates[Keyboard::Key::Enter].setValue(0);

	buttonStates[Gamepad::Button::A].setValue(0);
	buttonStates[Gamepad::Button::B].setValue(0);
	buttonStates[Gamepad::Button::X].setValue(0);
	buttonStates[Gamepad::Button::Y].setValue(0);
	buttonStates[Gamepad::Button::DPadUp].setValue(0);
	buttonStates[Gamepad::Button::DPadDown].setValue(0);
	buttonStates[Gamepad::Button::DPadLeft].setValue(0);
	buttonStates[Gamepad::Button::DPadRight].setValue(0);
	buttonStates[Gamepad::Button::LShoulder].setValue(0);
	buttonStates[Gamepad::Button::RShoulder].setValue(0);
	buttonStates[Gamepad::Button::LThumbstick].setValue(0);
	buttonStates[Gamepad::Button::RThumbstick].setValue(0);
	buttonStates[Gamepad::Button::Start].setValue(0);
	buttonStates[Gamepad::Button::Back].setValue(0);
}