// RPGTest
// State.hpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-10-27 by Justyn Durnford
// Header file for the State class.

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include "Time.hpp"
using jlib::Duration;

import Ptr;
using jlib::Ptr;

// 
class State
{
	public:

	Ptr<RenderWindow> window;
	bool shouldEnd;

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
};