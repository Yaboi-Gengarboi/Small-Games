// RPGTest
// Main.cpp
// Created on 2022-09-28 by Justyn Durnford
// Last modified on 2022-11-07 by Justyn Durnford
// Main file for the RPGTest project.

#include "RPGGame.hpp"

#include <iostream>

template <typename T>
void println(const T& value)
{
	std::cout << value << '\n';
}

void println(const std::string& str)
{
	std::cout << str << '\n';
}

int main(int argc, char** argv)
{
	RPGGame game;
	game.run();

	return 0;
}