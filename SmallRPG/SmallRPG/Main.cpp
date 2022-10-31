// SmallRPG
// Main.cpp
// Created on 2022-07-19 by Justyn Durnford
// Last modified on 2022-08-06 by Justyn Durnford
// Main file.

#include "Player.hpp"
#include "Room.hpp"
#include "RPGGame.hpp"

#include <filesystem>
using std::filesystem::current_path;

#include <iostream>
using std::cout;

import InputBuffer;
using jlib::InputBuffer;

int main()
{
	InputBuffer<u8> buff(0b10000000);

	for (int i = 0; i < sizeof(u8) * 8; ++i)
	{
		cout << buff.toString() << ": ";
		cout << static_cast<u16>(buff.getValue()) << '\n';
		buff.update(false);
	}

	RPGGame game;
	game.run();

	return 0;
}