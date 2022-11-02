// RPGTest
// State.cpp
// Created on 2022-09-30 by Justyn Durnford
// Last modified on 2022-11-01 by Justyn Durnford
// Source file for the State class.

#include "State.hpp"

State::State()
{
	window = nullptr;
	next = NONE;
}

State::State(Ptr<RenderWindow> new_window)
{
	window = new_window;
	next = NONE;
}