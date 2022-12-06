// RPGTest
// Enums.hpp
// Created on 2022-11-11 by Justyn Durnford.
// Last modified on 2022-11-11 by Justyn Durnford.
// Header file including several enums.

#pragma once

#include "IntegerTypedefs.hpp"
using jlib::u8;

// 
enum Collision : u8
{
	EMPTY    = 0,
	LOADZONE = 1,
	SOLID    = 2,
	WATER    = 3
};

// 
enum TravelMethod : u8
{
	WALKING = 0,
	RUNNING = 1,
	BIKING  = 2,
	SURFING = 3
};