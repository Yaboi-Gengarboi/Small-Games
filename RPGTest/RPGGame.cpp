// RPGTest
// RPGGame.cpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-11-02 by Justyn Durnford
// Source file for the RPGGame class.

#include "MainMenuState.hpp"
#include "OverworldState.hpp"
#include "RPGGame.hpp"

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
		states.top()->update(dt);

		if (states.top()->next == State::NextState::EXIT)
		{
			states.top()->end(current_path() / L"data");
			states.pop();
		}
		else if (states.top()->next == State::NextState::OVERWORLD)
		{
			states.top()->end(current_path() / L"data");
			states.pop();
			_window.display();

			thread thr(&RPGGame::loadOverworldState, this);



			// Wait for 2 seconds.
			_clock.startTimer();
			while (_clock.getElapsedTime() < Duration(2)) {}
			_clock.stopTimer();

			thr.join();
		}
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

void RPGGame::loadOverworldState()
{
	states.push(make_unique<OverworldState>(current_path() / L"data", &_window, inputManager.get()));
}

RPGGame::RPGGame() : Game(WINDOW_WIDTH, WINDOW_HEIGHT, "RPGTest")
{
	inputManager = make_unique<InputManager>();
	inputManager->setControllerDeadZones(0.2f, 0.2f, 0.2f, 0.2f);
	states.push(make_unique<MainMenuState>(current_path() / L"data", &_window, inputManager.get()));
}

RPGGame::RPGGame(u32 window_width, u32 window_height, const sf::String& title,
				 u32 style, const sf::ContextSettings& settings)
	: Game(window_width, window_height, title, style, settings)
{
	inputManager = make_unique<InputManager>();
	inputManager->setControllerDeadZones(0.2f, 0.2f, 0.2f, 0.2f);
	states.push(make_unique<MainMenuState>(current_path() / L"data", &_window, inputManager.get()));
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