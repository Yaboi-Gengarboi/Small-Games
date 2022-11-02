// RPGTest
// State.hpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-11-01 by Justyn Durnford
// Header file for the State class.

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include "IntegerTypedefs.hpp"
using jlib::u8;

#include "Time.hpp"
using jlib::Duration;

import Ptr;
using jlib::Ptr;

// 
class State
{
	public:

	enum NextState : u8
	{
		NONE = 0,
		EXIT = 1,
		OVERWORLD = 2
	};

	Ptr<RenderWindow> window;
	NextState next;

	// Default constructor.
	State();

	// Constructor.
	State(Ptr<RenderWindow> new_window);

	// Destructor.
	virtual ~State() = default;

	// 
	virtual void update(Duration dt) = 0;

	// 
	virtual void render() = 0;

	// 
	virtual void end() = 0;
};