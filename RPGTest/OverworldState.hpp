// RPGTest
// OverworldState.hpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-11-05 by Justyn Durnford
// Header file for the OverworldState class.

#pragma once

#include "Player.hpp"
#include "State.hpp"

#include <SFML/Graphics/Text.hpp>
using sf::Text;

#include <SFML/Graphics/View.hpp>
using sf::View;

class OverworldState : public State
{
	public:

	Player player;
	View camera;
	Ptr<Room> room;
	Ptr<InputManager> inputManager;

	// Default constructor.
	OverworldState();

	// Constructor.
	OverworldState(const path& folder, Ptr<RenderWindow> new_window, Ptr<InputManager> new_inputManager);

	// Destructor.
	~OverworldState() = default;

	// 
	void update(Duration dt);

	// 
	void render();

	// 
	void end(const path& folder);
};