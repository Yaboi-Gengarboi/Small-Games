// RPGTest
// OverworldState.hpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Header file for the OverworldState class.

#pragma once

#include "Player.hpp"
#include "State.hpp"

class OverworldState : public State
{
	public:

	View camera;

	#ifdef _DEBUG

	Text playerPosText;
	Text playerVelText;

	#endif // #ifdef _DEBUG

	// Default constructor.
	OverworldState();

	// Constructor.
	OverworldState(const path& folder, Ptr<RenderWindow> new_window);

	// Destructor.
	~OverworldState();

	// 
	void changeCurrentRoom(u16 new_room, const path& folder);

	// 
	void update(Duration dt, InputManager& input_manager);

	// 
	void render();

	// 
	void end(const path& folder);
};