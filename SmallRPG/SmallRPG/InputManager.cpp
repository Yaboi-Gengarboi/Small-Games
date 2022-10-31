// SmallRPG
// InputManager.cpp
// Created on 2022-07-31 by Justyn Durnford
// Last modified on 2022-08-06 by Justyn Durnford
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
	for (std::pair<const Keyboard::Key, InputBufferU8>& pair : keyStates)
	{
		if (Keyboard::isKeyPressed(pair.first))
			keyStates[pair.first].update(true);
		else
			keyStates[pair.first].update(false);
	}
}

void InputManager::_updateButtonStates()
{
	shift_right(buttonStates.begin(), buttonStates.end(), 1);
	buttonStates[0] = controller.getButtonStates();
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
}

u8 InputManager::getKeyState(Keyboard::Key key)
{
	return keyStates[key].getValue();
}

WORD InputManager::getButtonState(Gamepad::Button button)
{
	return controller.isButtonPressed(button);
}

//u16 InputManager::getDirectionState(const Direction& direction)
//{
//	u16 value = 0;
//
//	switch (direction.id)
//	{
//		case Direction::UP:
//			value = max(getKeyState(Keyboard::Key::W), getButtonState(Gamepad::Button::DPadUp));
//			break;
//
//		case Direction::RIGHT:
//			value = max(getKeyState(Keyboard::Key::D), getButtonState(Gamepad::Button::DPadRight));
//			break;
//
//		case Direction::DOWN:
//			value = max(getKeyState(Keyboard::Key::S), getButtonState(Gamepad::Button::DPadDown));
//			break;
//
//		case Direction::LEFT:
//			value = max(getKeyState(Keyboard::Key::A), getButtonState(Gamepad::Button::DPadLeft));
//			break;
//
//		default:
//			value = 0;
//			break;
//	}
//
//	return value;
//}

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