// RPGTest
// RPGGame.hpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Header file for the RPGGame class.

#pragma once

#include "Namespace.hpp"

#include "Game.hpp"
using jlib::Game;

#include "GameConstants.hpp"

#include "InputManager.hpp"

#include "State.hpp"

class RPGGame : public Game
{
	// 
	void processEvents();

	// 
	void update(Duration dt);

	// 
	void render();

	public:

	unique_ptr<InputManager> inputManager;
	stack<unique_ptr<State>, vector<unique_ptr<State>>> states;

	// 
	RPGGame();

	// 
	RPGGame(u32 window_width, u32 window_height, const sf::String& title,
			u32 style = jlib::nonScalableWindowStyle,
			const sf::ContextSettings& settings = sf::ContextSettings());

	// 
	void createNewSaveData(const path& folder);

	// 
	void readSaveData(const path& folder);

	// 
	void writeSaveData(const path& folder);

	// 
	void run();
};