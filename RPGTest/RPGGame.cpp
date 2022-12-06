// RPGTest
// RPGGame.cpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Source file for the RPGGame class.

#include "MainMenuState.hpp"
#include "OverworldState.hpp"
#include "PauseMenuState.hpp"
#include "Resources.hpp"
#include "RPGGame.hpp"

void RPGGame::processEvents()
{
	inputManager->update(_window);

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

	inputManager->update(_window);

	// Update states.
	if (!states.empty() && _window.hasFocus())
	{
		states.top()->update(dt, *inputManager);

		if (states.top()->next == State::NextState::NONE)
		{

		}
		else if (states.top()->next == State::NextState::EXIT)
		{
			while (!states.empty())
			{
				states.top()->end(current_path() / L"data");
				states.pop();
			}
		}
		else if (states.top()->next == State::NextState::END)
		{
			inputManager->reset();
			inputManager->sleepFor(Duration(0.5f));
			states.top()->end(current_path() / L"data");
			states.pop();
			_window.display();
		}
		else if (states.top()->next == State::NextState::SAVE)
		{
			inputManager->reset();
			inputManager->sleepFor(Duration(0.5f));

			writeSaveData(current_path() / L"data");

			cout << "Save data written\n";
			states.top()->next = State::NextState::NONE;
		}
		else if (states.top()->next == State::NextState::NEWGAME)
		{
			inputManager->reset();
			inputManager->sleepFor(Duration(0.5f));

			states.top()->end(current_path() / L"data");
			_window.display();

			createNewSaveData(current_path() / L"data");
		}
		else if (states.top()->next == State::NextState::MAINMENU)
		{
			inputManager->reset();
			inputManager->sleepFor(Duration(0.5f));

			states.top()->end(current_path() / L"data");
			_window.display();

			states.push(make_unique<MainMenuState>(current_path() / L"data", &_window));
		}
		else if (states.top()->next == State::NextState::OVERWORLD)
		{
			inputManager->reset();
			inputManager->sleepFor(Duration(0.5f));

			states.top()->end(current_path() / L"data");
			_window.display();

			states.push(make_unique<OverworldState>(current_path() / L"data", &_window));
		}
		else if (states.top()->next == State::NextState::PAUSEMENU)
		{
			inputManager->reset();
			inputManager->sleepFor(Duration(0.5f));

			states.top()->next = State::NextState::NONE;

			states.push(make_unique<PauseMenuState>(current_path() / L"data", &_window));
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

RPGGame::RPGGame() : Game(WINDOW_WIDTH, WINDOW_HEIGHT, "RPGTest")
{
	inputManager = make_unique<InputManager>();
	inputManager->setControllerDeadZones(0.2f, 0.2f, 0.2f, 0.2f);
	readSaveData(current_path() / L"data");
	states.push(make_unique<MainMenuState>(current_path() / L"data", &_window));
}

RPGGame::RPGGame(u32 window_width, u32 window_height, const sf::String& title,
				 u32 style, const sf::ContextSettings& settings)
	: Game(window_width, window_height, title, style, settings)
{
	inputManager = make_unique<InputManager>();
	inputManager->setControllerDeadZones(0.2f, 0.2f, 0.2f, 0.2f);
	readSaveData(current_path() / L"data");
	states.push(make_unique<MainMenuState>(current_path() / L"data", &_window));
}

void RPGGame::createNewSaveData(const path& folder)
{
	#ifdef _DEBUG
	cout << "Creating save data...\n";
	#endif // #ifdef _DEBUG

	path file(folder / L"save_data.txt");

	if (!exists(file))
		Player::loadFail(file, wstring(L"Could not locate file: ") + file.wstring());

	ofstream fout(file);

	fout << rand_u16() << '\n';
	fout << "Player\n";
	fout << 0u << '\n';
	fout << 0u << '\n';
	fout << to_string(Vector2f(768.0f, 768.0f));

	fout.close();
	states.push(make_unique<OverworldState>(folder, &_window));
}

void RPGGame::readSaveData(const path& folder)
{
	#ifdef _DEBUG
	cout << "Reading save and player data...\n";
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
		cout << to_string(dir_id) << '\n';
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

	player = make_shared<Player>(new_id, new_name, new_position, Vector2f(0.0f, 0.0f), directions[dir_id], &(room_arr[room_id]));
	player->loadSpriteData(current_path() / L"data");
}

void RPGGame::writeSaveData(const path& folder)
{
	path file(folder / L"save_data.txt");

	if (!exists(file))
		Player::loadFail(file, wstring(L"Could not locate file: ") + file.wstring());

	ifstream fin(file);
	vector<string> lines;
	string line;

	while (getline(fin, line))
		lines.push_back(line);

	if (player->currentDirection)
		lines[2] = to_string(player->currentDirection->id);

	lines[4] = to_string(player->position);

	fin.close();

	ofstream fout(file);

	for (size_t i = 0; i < lines.size(); ++i)
		fout << lines[i] << '\n';

	fout.close();
}

void RPGGame::run()
{
	// Start the loop.
	while (_window.isOpen())
	{
		processEvents();
		update(resources->main_clock.restartTimer());
		render();
	}
}