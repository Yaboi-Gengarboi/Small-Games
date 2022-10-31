// SmallRPG
// RPGGame.cpp
// Created on 2022-08-02 by Justyn Durnford
// Last modified on 2022-08-03 by Justyn Durnford
// Source file for the RPGGame class.

#include "OverworldState.hpp"

#include "RPGGame.hpp"

#include <SFML/Window/Event.hpp>
using sf::Event;

void RPGGame::processEvents()
{
	inputManager->update(&_window);

	// Process events.
	while (_window.pollEvent(_event))
	{
		switch (_event.type)
		{
			// Close window: exit.
			case Event::Closed:
				_window.close();
			break;

			default: break;
		}
	}
}
 
void RPGGame::update(Duration dt)
{
	if (states.empty())
		_window.close();

	// 
	inputManager->update(&_window);

	// Update states.
	if (!states.empty())
	{
		states.top()->update(dt, inputManager.get());
		if (states.top()->shouldEnd)
			states.pop();
	}
}

void RPGGame::render()
{
	// Clear screen.
	_window.clear();

	// Render states.
	if (!states.empty())
		states.top()->render();

	// Display the window's contents.
	_window.display();
}

RPGGame::RPGGame() : Game()
{
	inputManager = make_unique<InputManager>();
	states.push(make_unique<OverworldState>(&_window, 0));
}

RPGGame::RPGGame(u32 window_width, u32 window_height, const sf::String& title,
		u32 style, const sf::ContextSettings& settings)
	: Game(window_width, window_height, title, style, settings)
{
	inputManager = make_unique<InputManager>();
	states.push(make_unique<OverworldState>(&_window, 0));
}

void RPGGame::run()
{
	// Start the loop.
	while (_window.isOpen())
	{
		processEvents();
		update(_clock.restartTimer());
		render();
	}
}