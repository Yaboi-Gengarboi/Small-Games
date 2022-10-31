// SmallRPG
// OverworldState.cpp
// Created on 2022-08-01 by Justyn Durnford
// Last modified on 2022-08-03 by Justyn Durnford
// Source file for the OverworldState class.

#include "GameConstants.hpp"
#include "OverworldState.hpp"
#include "Room.hpp"
#include "SFMLFunctions.hpp"

OverworldState::OverworldState() : State(), player(L"Data\\Player")
{

}

OverworldState::OverworldState(Ptr<RenderWindow> window, u16 room_ID) : State(window), player(L"Data\\Player")
{
	load_room(room_ID, L"Data\\Rooms");
	screen.reset(sf::FloatRect(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT));
	screen.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	currentPlayerRoom = &room_arr[room_ID];
}

void OverworldState::update(Duration dt, Ptr<InputManager> inputManager)
{
	if (inputManager->getKeyState(Keyboard::Key::Escape))
		shouldEnd = true;
	else
	{
		player.update(dt, inputManager, currentPlayerRoom);
		screen.setCenter(player.spritePosition.x + 48.0f, player.spritePosition.y + 48.0f);
	}
}

void OverworldState::render()
{
	windowPtr->setView(screen);
	windowPtr->draw(currentPlayerRoom->sprite);
	player.render(windowPtr);
}