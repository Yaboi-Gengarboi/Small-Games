// RPGTest
// MainMenuState.hpp
// Created on 2022-10-30 by Justyn Durnford
// Last modified on 2022-11-02 by Justyn Durnford
// Header file for the MainMenuState class.

#include "MainMenuState.hpp"
#include "SFMLFunctions.hpp"

#include <fstream>
using std::ifstream;

#include <iostream>
using std::cout;
using std::wcout;
using std::wcerr;

MainMenuState::MainMenuState(const path& folder, Ptr<RenderWindow> new_window, Ptr<InputManager> new_inputManager) : State(new_window)
{
	#ifdef _DEBUG
	cout << "Loading main menu...\n";
	#endif // #ifdef _DEBUG

	path file(folder / L"menus\\main\\background.png");

	if (!exists(file))
		loadFail(file, wstring(L"Could not locate file: ") + file.wstring());

	create_texture(backgroundTexture, file);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(2.0f, 2.0f);

	inputManager = new_inputManager;
}

void MainMenuState::loadFail(const path& filepath, const wstring& message)
{
	wcerr << L"Error encountered while loading the main menu from file: " << filepath.wstring() << L'\n';
	wcerr << message << L'\n';
	exit(1);
}

void MainMenuState::update(Duration dt)
{
	inputManager->update(window);

	if (inputManager->getKeyState(Keyboard::Escape))
		next = State::NextState::EXIT;
	else if (inputManager->getKeyState(Keyboard::Enter))
		next = State::NextState::OVERWORLD;
}

void MainMenuState::render()
{
	if (window)
	{
		window->draw(backgroundSprite);
	}
}

void MainMenuState::end(const path& folder)
{
	if (window)
	{
		window->clear(sf::Color::Black);
	}
}