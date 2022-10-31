// SmallRPG
// GameConstants.hpp
// Created on 2022-08-01 by Justyn Durnford
// Last modified on 2022-08-02 by Justyn Durnford
// Header file defining several universal game constants.

#pragma once

#include "IntegerTypedefs.hpp"
using jlib::u32;

#include <thread>

// Default window width.
constexpr u32 WINDOW_WIDTH = 768u;

// Default window height.
constexpr u32 WINDOW_HEIGHT = 768u;

// Universal sprite scale factor.
static float SCALE = 2.0f;

constexpr u32 TILE_LENGTH = 32u;
const static u32 CPU_CORES = std::thread::hardware_concurrency();