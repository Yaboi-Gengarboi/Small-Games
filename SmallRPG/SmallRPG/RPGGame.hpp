// SmallRPG
// RPGGame.hpp
// Created on 2022-08-02 by Justyn Durnford
// Last modified on 2022-08-02 by Justyn Durnford
// Header file for the RPGGame class.

#pragma once

#include "Game.hpp"
using jlib::Game;

#include "GameConstants.hpp"

#include "InputManager.hpp"

#include "State.hpp"

#include "Time.hpp"
using jlib::Duration;

#include <memory>
using std::unique_ptr;
using std::make_unique;

#include <stack>
using std::stack;

#include <vector>
using std::vector;

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
	void run();
};