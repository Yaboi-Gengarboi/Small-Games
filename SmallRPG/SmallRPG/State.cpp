// SmallRPG
// State.cpp
// Created on 2022-07-31 by Justyn Durnford
// Last modified on 2022-07-31 by Justyn Durnford
// Source file for the State class.

#include "State.hpp"

State::State()
{
	windowPtr = nullptr;
}

State::State(Ptr<RenderWindow> new_windowPtr)
{
	windowPtr = new_windowPtr;
}