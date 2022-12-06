// RPGTest
// InputManager.hpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Header file for the InputManager class.

#pragma once

#include "Namespace.hpp"

// 
class InputManager
{
	// 
	void _updateKeyStates();

	// 
	void _updateButtonStates();

	public:

	Vector2f mousePosition;
	Gamepad controller;

	unordered_map<Keyboard::Key, InputBuffer> keyStates;
	unordered_map<Gamepad::Button, InputBuffer> buttonStates;

	TimePoint sleepStart;
	Duration sleepTime;

	// Default constructor.
	InputManager();

	// 
	void setControllerDeadZones(float lx_dz, float ly_dz, float rx_dz, float ry_dz);

	// 
	bool getCurrentKeyState(Keyboard::Key key);

	// 
	u16 getKeyState(Keyboard::Key key);

	// 
	bool getCurrentButtonState(Gamepad::Button button);

	// 
	u16 getButtonState(Gamepad::Button button);

	// 
	Ptr<const Direction> getCurrentDirection();

	// 
	void sleepFor(Duration secs);

	// 
	void update(RenderWindow& window);

	// 
	void reset();
};