// RPGTest
// OverworldState.cpp
// Created on 2022-10-12 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Source file for the OverworldState class.

#include "GameConstants.hpp"
#include "Mouse.hpp"
#include "OverworldState.hpp"
#include "Resources.hpp"
#include "Room.hpp"
#include "SFMLFunctions.hpp"

OverworldState::OverworldState() : State()
{

}

OverworldState::OverworldState(const path& folder, Ptr<RenderWindow> new_window) : State(new_window)
{
	camera.reset(sf::FloatRect(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT));
	camera.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

	#ifdef _DEBUG

	create_text(playerPosText, camera.getCenter(), to_string(player->position), resources->consolas_font,
				24u, sf::Text::Bold, sf::Color::White, sf::Color::Black, 3.0f);

	create_text(playerVelText, camera.getCenter(), to_string(player->position), resources->consolas_font,
				24u, sf::Text::Bold, sf::Color::White, sf::Color::Black, 3.0f);

	#endif // #ifdef _DEBUG
}

OverworldState::~OverworldState()
{
	#ifdef _DEBUG
	cout << "Overworld State ending.\n";
	#endif // #ifdef _DEBUG
}

void OverworldState::changeCurrentRoom(u16 new_room, const path& folder)
{
	window->clear(sf::Color::Black);

	thread thr(load_room, new_room, folder);
	sleep_for(seconds(2));
	thr.join();
}

void OverworldState::update(Duration dt, InputManager& input_manager)
{
	if (input_manager.getCurrentKeyState(Keyboard::Escape))
		next = State::NextState::PAUSEMENU;

	player->update(dt, input_manager);

	#ifdef _DEBUG

	playerPosText.setPosition(camera.getCenter().x - WINDOW_WIDTH / 2.0f, camera.getCenter().y - WINDOW_HEIGHT / 2.0f);
	playerVelText.setPosition(camera.getCenter().x - WINDOW_WIDTH / 2.0f, camera.getCenter().y - WINDOW_HEIGHT / 2.0f + 24.0f);

	playerPosText.setString(to_string(player->position));
	playerVelText.setString(to_string(player->velocity));
	
	#endif // #ifdef _DEBUG

	/*if (are_all_equal_to(player.vertexCollisionStates.data(), player.vertexCollisionStates.data() + 4, Collision::LOADZONE))
	{
		for (size_t i = 0; i < room->loadZones.size(); ++i)
		{
			if (room->loadZones[i].box.contains(player.position))
				changeCurrentRoom(room->loadZones[i].nextRoom, current_path());
		}
	}*/

	camera.setCenter(player->position.x + Player::SPRITE_WIDTH / 2.0f, player->position.y + Player::SPRITE_HEIGHT / 2.0f);
}

void OverworldState::render()
{
	window->draw(player->room->sprite);

	#ifdef _DEBUG

	window->draw(playerPosText);
	window->draw(playerVelText);

	#endif // #ifdef _DEBUG

	window->setView(camera);
	player->render(*window);
}

void OverworldState::end(const path& folder)
{
	next = State::NextState::NONE;
	window->setView(window->getDefaultView());
	window->clear(sf::Color::Black);
}