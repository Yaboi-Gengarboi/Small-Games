// SmallRPG
// OverworldState.hpp
// Created on 2022-08-01 by Justyn Durnford
// Last modified on 2022-08-01 by Justyn Durnford
// Header file for the OverworldState class.

#pragma once

#include "Player.hpp"
#include "State.hpp"

#include <SFML/Graphics/View.hpp>
using sf::View;

class OverworldState : public State
{
	public:

	Ptr<Room> currentPlayerRoom;
	Player player;
	View screen;

	// Default constructor.
	OverworldState();

	// Constructor.
	OverworldState(Ptr<RenderWindow> window, u16 room_ID);

	// Destructor.
	~OverworldState() = default;

	// 
	void update(Duration dt, Ptr<InputManager> inputManager);

	// 
	void render();
};