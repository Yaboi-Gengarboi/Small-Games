// SmallRPG
// State.hpp
// Created on 2022-07-31 by Justyn Durnford
// Last modified on 2022-07-31 by Justyn Durnford
// Header file for the State class.

#pragma once

#include "InputManager.hpp"

#include "Time.hpp"
using jlib::Duration; 

class State
{
	public:

	Ptr<RenderWindow> windowPtr;
	bool shouldEnd;

	// Default constructor.
	State();

	// Constructor.
	State(Ptr<RenderWindow> new_windowPtr);

	// Destructor.
	virtual ~State() = default;

	// 
	virtual void update(Duration dt, Ptr<InputManager> inputManager) = 0;

	// 
	virtual void render() = 0;
};