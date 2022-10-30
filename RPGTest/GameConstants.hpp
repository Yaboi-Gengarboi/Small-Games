// SRPGTest
// GameConstants.hpp
// Created on 2022-10-09 by Justyn Durnford
// Last modified on 2022-10-28 by Justyn Durnford
// Header file defining several universal game constants.

#pragma once

#include "Direction.hpp"
using jlib::Direction;

#include "IntegerTypedefs.hpp"
using jlib::u32;

#include <array>
using std::array;

#include <thread>

import Ptr;
using jlib::Ptr;

// Default window width.
constexpr u32 WINDOW_WIDTH = 1536u;

// Default window height.
constexpr u32 WINDOW_HEIGHT = 1024u;

// Universal sprite scale factor.
constexpr float SCALE = 8.0f;

// 
constexpr float TILE_LENGTH = 16.0f;

// 
constexpr float PLAYER_WALK_SPEED = TILE_LENGTH * SCALE * 4.0f;

// 
constexpr float PLAYER_SPRITE_WIDTH = 128.0f;

// 
constexpr float PLAYER_SPRITE_HEIGHT = 128.0f;

// 
constexpr float PLAYER_SPRITE_X_OFFSET = PLAYER_SPRITE_WIDTH / 2.0f;

// 
constexpr float PLAYER_SPRITE_Y_OFFSET = PLAYER_SPRITE_HEIGHT / 2.0f;

// 
const static u32 CPU_CORES = std::thread::hardware_concurrency();

// 
const static array<Ptr<const Direction>, 8> directions =
{
	Ptr<const Direction>(&Direction::North),
	Ptr<const Direction>(&Direction::Northeast),
	Ptr<const Direction>(&Direction::East),
	Ptr<const Direction>(&Direction::Southeast),
	Ptr<const Direction>(&Direction::South),
	Ptr<const Direction>(&Direction::Southwest),
	Ptr<const Direction>(&Direction::West),
	Ptr<const Direction>(&Direction::Northwest)
};