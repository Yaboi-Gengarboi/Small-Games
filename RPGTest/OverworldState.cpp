// RPGTest
// OverworldState.cpp
// Created on 2022-10-12 by Justyn Durnford
// Last modified on 2022-11-01 by Justyn Durnford
// Source file for the OverworldState class.

#pragma warning( disable : 4244 ) 

#include "GameConstants.hpp"
#include "Mouse.hpp"
#include "OverworldState.hpp"
#include "Resources.hpp"
#include "Room.hpp"
#include "SFMLFunctions.hpp"

#include <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

#include <fstream>
using std::ifstream;

#include <iostream>
using std::cout;
using std::wcout;
using std::wcerr;

#include <string>
using std::string;
using std::wstring;
using std::getline;
using std::stoi;
using std::to_string;
using std::to_wstring;

OverworldState::OverworldState() : State()
{

}

OverworldState::OverworldState(const path& folder, Ptr<RenderWindow> new_window, Ptr<InputManager> new_inputManager) : State(new_window)
{
	#ifdef _DEBUG
	cout << "Loading player data...\n";
	#endif // #ifdef _DEBUG

	path file(folder / L"save_data.txt");

	if (!exists(file))
		Player::loadFail(file, wstring(L"Could not locate file: ") + file.wstring());

	ifstream fin(file);

	int new_id = 0, dir_id = 0, room_id = 0;
	string line, new_name;
	Vector2f new_position;

	try
	{
		if (!getline(fin, line))
			throw;

		new_id = stoi(line);

		#ifdef _DEBUG
		cout << to_string(new_id) << '\n';
		#endif // #ifdef _DEBUG
	}
	catch (...)
	{
		Player::loadFail(file, L"Could not read ID of Player.");
	}

	try
	{
		if (!getline(fin, line))
			throw;

		new_name = line;

		#ifdef _DEBUG
		cout << new_name << '\n';
		#endif // #ifdef _DEBUG
	}
	catch (...)
	{
		Player::loadFail(file, L"Could not read name of Player.");
	}

	try
	{
		if (!getline(fin, line))
			throw;

		dir_id = stoi(line);

		#ifdef _DEBUG
		cout << to_string(new_id) << '\n';
		#endif // #ifdef _DEBUG
	}
	catch (...)
	{
		Player::loadFail(file, L"Could not read direction of Player.");
	}

	try
	{
		if (!getline(fin, line))
			throw;

		room_id = stoi(line);

		#ifdef _DEBUG
		cout << to_string(room_id) << '\n';
		#endif // #ifdef _DEBUG
	}
	catch (...)
	{
		Player::loadFail(file, L"Could not current room of Player.");
	}

	try
	{
		if (!getline(fin, line))
			throw;

		new_position = jlib::str_to_vec2_f32(line);

		#ifdef _DEBUG
		cout << new_position << "\n\n";
		#endif // #ifdef _DEBUG
	}
	catch (...)
	{
		Player::loadFail(file, L"Could not read position of Player.");
	}

	if (!load_room(room_id, folder))
	{
		wcerr << L"Error: Could not load room: " << to_wstring(room_id) << L'\n';
		exit(1);
	}

	room = &room_arr[room_id];
	inputManager = new_inputManager;
	player = Player(new_id, new_name, new_position, Vector2f(0.0f, 0.0f), directions[dir_id], inputManager, room);
	player.loadSpriteData(folder);

	camera.reset(sf::FloatRect(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT));
	camera.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
}

void OverworldState::update(Duration dt)
{
	inputManager->update(window);

	if (inputManager->getKeyState(Keyboard::Escape))
		next = State::NextState::EXIT;

	player.update(dt);

	camera.setCenter(player.position.x + PLAYER_SPRITE_WIDTH / 2.0f, player.position.y + PLAYER_SPRITE_HEIGHT / 2.0f);
}

void OverworldState::render()
{
	if (window)
	{
		window->draw(room->sprite);
		window->setView(camera);
		player.render(*window);
	}
}

void OverworldState::end()
{
	if (window)
	{
		window->clear(sf::Color::Black);
	}
}