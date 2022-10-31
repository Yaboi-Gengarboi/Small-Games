// SmallRPG
// InputManager.hpp
// Created on 2022-07-30 by Justyn Durnford
// Last modified on 2022-08-06 by Justyn Durnford
// Header file for the InputManager class.

#pragma once

#include "Direction.hpp"
using jlib::Direction;

#include "InputBuffer.hpp"

#include "IntegerTypedefs.hpp"
using jlib::u8;
using jlib::u16;

#include "Gamepad.hpp"
using jlib::Gamepad;

#include <SFML/Window/Keyboard.hpp>
using sf::Keyboard;

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <array>
using std::array;

#include <bitset>
using std::bitset;

#include <unordered_map>
using std::unordered_map;

import FixedArray;
using jlib::FixedArray;

import Ptr;
using jlib::Ptr;

import Vector2;
using jlib::Vector2i;

class InputManager
{
	// 
	void _updateKeyStates();

	// 
	void _updateButtonStates();

	public:

	Vector2i mousePosition;
	Gamepad controller;

	unordered_map<Keyboard::Key, InputBufferU8> keyStates;
	FixedArray<WORD, 8> buttonStates;

	// Default constructor.
	InputManager();

	// 
	bool getCurrentKeyState(Keyboard::Key key);

	// 
	u8 getKeyState(Keyboard::Key key);

	// 
	bool getCurrentButtonState(Gamepad::Button button);

	// 
	WORD getButtonState(Gamepad::Button button);
	
	// 
	// u16 getDirectionState(const Direction& direction);

	// 
	void update(Ptr<RenderWindow> window);
};