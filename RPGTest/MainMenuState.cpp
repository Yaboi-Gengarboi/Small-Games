// RPGTest
// MainMenuState.hpp
// Created on 2022-10-30 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Header file for the MainMenuState class.

#include "MainMenuState.hpp"
#include "Resources.hpp"
#include "SFMLFunctions.hpp"

MainMenuState::MainMenuState(const path& folder, Ptr<RenderWindow> new_window) : State(new_window), 
	newGameButton(FloatRect(100, 200, 300, 100), resources->pokemon_ds_font, Text("New Game", resources->pokemon_ds_font, 64u), Color::Gray, Color::DarkGray, Color::LightGray),
	loadGameButton(FloatRect(100, 350, 300, 100), resources->pokemon_ds_font, Text("Load Game", resources->pokemon_ds_font, 64u), Color::Gray, Color::DarkGray, Color::LightGray),
	exitGameButton(FloatRect(100, 500, 300, 100), resources->pokemon_ds_font, Text("Exit Game", resources->pokemon_ds_font, 64u), Color::Gray, Color::DarkGray, Color::LightGray)
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

	newGameButton.text.setCharacterSize(64u);
	newGameButton.text.setOutlineThickness(3.0f);

	loadGameButton.text.setCharacterSize(64u);
	loadGameButton.text.setOutlineThickness(3.0f);

	exitGameButton.text.setCharacterSize(64u);
	exitGameButton.text.setOutlineThickness(3.0f);

	testComboBox = ComboBox(800, 200, 300, 100);
	testComboBox.addElement();
	testComboBox.addElement();
}

MainMenuState::~MainMenuState()
{
	#ifdef _DEBUG
	cout << "MainMenu State ending.\n";
	#endif // #ifdef _DEBUG
}

void MainMenuState::loadFail(const path& filepath, const wstring& message)
{
	wcerr << L"Error encountered while loading the main menu from file: " << filepath.wstring() << L'\n';
	wcerr << message << L'\n';
	exit(1);
}

void MainMenuState::update(Duration dt, InputManager& input_manager)
{
	newGameButton.update(dt, input_manager);
	loadGameButton.update(dt, input_manager);
	exitGameButton.update(dt, input_manager);
	testComboBox.update(dt, input_manager);

	if (input_manager.getCurrentKeyState(Keyboard::Escape))
		cout << "Escape\n";

	if (input_manager.getCurrentKeyState(Keyboard::Escape) || exitGameButton.state == Button::State::RELEASED)
		next = State::NextState::EXIT;
	else if (input_manager.getKeyState(Keyboard::Enter) || input_manager.getButtonState(Gamepad::Button::A))
		next = State::NextState::OVERWORLD;
	else if (newGameButton.state == Button::State::RELEASED)
		next = State::NextState::NEWGAME;
	else if (loadGameButton.state == Button::State::RELEASED)
		next = State::NextState::OVERWORLD;
}

void MainMenuState::render()
{
	window->draw(backgroundSprite);
	newGameButton.render(*window);
	loadGameButton.render(*window);
	exitGameButton.render(*window);
	testComboBox.render(*window);
}

void MainMenuState::end(const path& folder)
{
	next = State::NextState::NONE;
	window->clear(sf::Color::Black);
}