// RPGTest
// Main.cpp
// Created on 2022-09-28 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Main file for the RPGTest project.

#include "Player.hpp"
#include "RPGGame.hpp"
#include "Resources.hpp"

unique_ptr<Resources> resources = make_unique<Resources>();
shared_ptr<Player> player;

template <typename T>
void println(const T& value)
{
	cout << value << '\n';
}

void println(bool b)
{
	if (b)
		cout << "true" << '\n';
	else
		cout << "false" << '\n';
}

void println(const string& str)
{
	cout << str << '\n';
}

int main(int argc, char** argv)
{
	#ifdef _DEBUG
	cout << "Loading consolas font...\n";
	#endif // #ifdef _DEBUG

	path consolas_font_file(current_path() / L"data\\fonts\\consolas.ttf");
	if (!resources->consolas_font.loadFromFile(consolas_font_file.string()))
	{
		wcerr << L"ERROR: Could not load font from file: " << consolas_font_file << L"\n";
		exit(1);
	}

	#ifdef _DEBUG
	cout << "Loading pokemon_ds_font_file font...\n";
	#endif // #ifdef _DEBUG

	path pokemon_ds_font_file(current_path() / L"data\\fonts\\pokemon-ds-font.ttf");
	if (!resources->pokemon_ds_font.loadFromFile(pokemon_ds_font_file.string()))
	{
		wcerr << L"ERROR: Could not load font from file: " << pokemon_ds_font_file << L"\n";
		exit(1);
	}

	RPGGame game;
	game.run();

	return 0;
}