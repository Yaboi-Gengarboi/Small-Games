// RPGTest
// PauseMenuState.cpp
// Created on 2022-11-30 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Source file for the PauseMenuState class.

#include "PauseMenuState.hpp"
#include "GameConstants.hpp"
#include "Resources.hpp"

PauseMenuState::PauseMenuState(const path& folder, Ptr<RenderWindow> new_window) : State(new_window),
	resumeButton(FloatRect(), resources->pokemon_ds_font, Text("Resume", resources->pokemon_ds_font, 64u), Color::Gray, Color::DarkGray, Color::LightGray),
	saveButton(FloatRect(), resources->pokemon_ds_font, Text("Save", resources->pokemon_ds_font, 64u), Color::Gray, Color::DarkGray, Color::LightGray),
	exitButton(FloatRect(), resources->pokemon_ds_font, Text("Exit", resources->pokemon_ds_font, 64u), Color::Gray, Color::DarkGray, Color::LightGray)
{
	Vector2f center(Vector2f(window->getView().getCenter()) - Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));
	Vector2f size(window->getView().getSize());

	FloatRect view_rect(center, size);

	background.setPosition(view_rect.vertex.x, view_rect.vertex.y);
	background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	background.setFillColor(sf::Color::White);

	resumeButton.setPosition(view_rect.averageX() - 150.0f, view_rect.averageY() - 200.0f);
	resumeButton.setSize(300.0f, 200.0f);

	saveButton.setPosition(view_rect.averageX() - 150.0f, view_rect.averageY());
	saveButton.setSize(300.0f, 200.0f);

	exitButton.setPosition(view_rect.averageX() - 150.0f, view_rect.averageY() + 200.0f);
	exitButton.setSize(300.0f, 200.0f);
}

PauseMenuState::~PauseMenuState()
{
	#ifdef _DEBUG
	cout << "PauseMenu State ending.\n";
	#endif // #ifdef _DEBUG
}

void PauseMenuState::update(Duration dt, InputManager& input_manager)
{
	exitButton.update(dt, input_manager);
	saveButton.update(dt, input_manager);
	resumeButton.update(dt, input_manager);

	if (exitButton.state == Button::State::RELEASED || input_manager.getCurrentKeyState(Keyboard::Key::Escape))
		next = State::NextState::EXIT;
	else if (saveButton.state == Button::State::RELEASED)
		next = State::NextState::SAVE;
	else if (resumeButton.state == Button::State::RELEASED)
		next = State::NextState::END;
}

void PauseMenuState::render()
{
	window->draw(background);
	resumeButton.render(*window);
	saveButton.render(*window);
	exitButton.render(*window);
}

void PauseMenuState::end(const path& folder)
{
	next = State::NextState::NONE;
}