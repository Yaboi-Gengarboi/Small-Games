// RPGTest
// State.cpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-10-22 by Justyn Durnford
// Source file for the State class.

#include "State.hpp"

State::State()
{
	window = nullptr;
	shouldEnd = false;
}

State::State(Ptr<RenderWindow> new_window)
{
	window = new_window;
	shouldEnd = false;
}