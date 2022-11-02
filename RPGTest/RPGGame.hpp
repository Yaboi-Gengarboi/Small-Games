// RPGTest
// RPGGame.hpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-11-01 by Justyn Durnford
// Header file for the RPGGame class.

#pragma once

#include <SFML/Window/Event.hpp>
using sf::Event;

#include "Game.hpp"
using jlib::Game;

#include "GameConstants.hpp"

#include "InputManager.hpp"

#include "State.hpp"

#include "Time.hpp"
using jlib::Duration;
using jlib::TimePoint;

#include <filesystem>
using std::filesystem::path;
using std::filesystem::current_path;
using std::filesystem::exists;

#include <memory>
using std::unique_ptr;
using std::make_unique;

#include <stack>
using std::stack;

#include <thread>
using std::thread;

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

	// 
	void loadOverworldState();

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