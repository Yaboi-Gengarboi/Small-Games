// RPGTest
// MainMenuState.hpp
// Created on 2022-10-30 by Justyn Durnford
// Last modified on 2022-12-03 by Justyn Durnford
// Header file for the MainMenuState class.

#pragma once

#include "Button.hpp"
#include "ComboBox.hpp"
#include "State.hpp"

class MainMenuState : public State
{
	public:

	Texture backgroundTexture;
	Sprite backgroundSprite;
	Button newGameButton;
	Button loadGameButton;
	Button exitGameButton;
	ComboBox testComboBox;

	// Default constructor.
	MainMenuState() = default;

	// Constructor.
	MainMenuState(const path& folder, Ptr<RenderWindow> new_window);

	// Destructor.
	~MainMenuState();

	// 
	static void loadFail(const path& filepath, const wstring& message);

	// 
	void update(Duration dt, InputManager& input_manager);

	// 
	void render();

	// 
	void end(const path& folder);
};