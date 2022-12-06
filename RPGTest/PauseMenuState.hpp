// RPGTest
// PauseMenuState.hpp
// Created on 2022-11-30 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Header file for the PauseMenuState class.

#pragma once

#include "Button.hpp"
#include "ComboBox.hpp"
#include "State.hpp"

class PauseMenuState : public State
{
	public:

	RectangleShape background;
	Text text;
	Button resumeButton;
	Button saveButton;
	Button exitButton;

	// Default constructor.
	PauseMenuState() = default;

	// Constructor.
	PauseMenuState(const path& folder, Ptr<RenderWindow> new_window);

	// Destructor.
	~PauseMenuState();

	// 
	void update(Duration dt, InputManager& input_manager);

	// 
	void render();

	// 
	void end(const path& folder);
};