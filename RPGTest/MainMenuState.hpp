// RPGTest
// MainMenuState.hpp
// Created on 2022-10-30 by Justyn Durnford
// Last modified on 2022-11-01 by Justyn Durnford
// Header file for the MainMenuState class.

#pragma once

#include "InputManager.hpp"
#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
using sf::Sprite;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

#include <string>
using std::string;
using std::wstring;
using std::getline;
using std::stoi;
using std::to_string;
using std::to_wstring;

class MainMenuState : public State
{
	public:

	Texture backgroundTexture;
	Sprite backgroundSprite;
	Ptr<InputManager> inputManager;

	// Default constructor.
	MainMenuState() = default;

	// Constructor.
	MainMenuState(const path& folder, Ptr<RenderWindow> new_window, Ptr<InputManager> new_inputManager);

	// Destructor.
	~MainMenuState() = default;

	// 
	static void loadFail(const path& filepath, const wstring& message);

	// 
	void update(Duration dt);

	// 
	void render();

	// 
	void end();
};