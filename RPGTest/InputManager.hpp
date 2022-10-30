// RPGTest
// InputManager.hpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-10-27 by Justyn Durnford
// Header file for the InputManager class.

#pragma once

#include "Direction.hpp"
using jlib::Direction;

#include "IntegerTypedefs.hpp"
using jlib::u8;

#include "Gamepad.hpp"
using jlib::Gamepad;

#include <SFML/Window/Keyboard.hpp>
using sf::Keyboard;

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <array>
using std::array;

#include <unordered_map>
using std::unordered_map;

import InputBuffer;
using jlib::InputBuffer;

import Ptr;
using jlib::Ptr;

import Vector2;
using jlib::Vector2i;

// 
class InputManager
{
	// 
	void _updateKeyStates();

	// 
	void _updateButtonStates();

	public:

	Vector2i mousePosition;
	Gamepad controller;

	unordered_map<Keyboard::Key, InputBuffer<u8>> keyStates;
	unordered_map<Gamepad::Button, InputBuffer<u8>> buttonStates;

	// Default constructor.
	InputManager();

	// 
	void setControllerDeadZones(float lx_dz, float ly_dz, float rx_dz, float ry_dz);

	// 
	bool getCurrentKeyState(Keyboard::Key key);

	// 
	u8 getKeyState(Keyboard::Key key);

	// 
	bool getCurrentButtonState(Gamepad::Button button);

	// 
	u8 getButtonState(Gamepad::Button button);

	// 
	Ptr<const Direction> getCurrentDirection();

	// 
	void update(Ptr<RenderWindow> window);
};