// Connect4
// Define.hpp
// Created on 2022-03-22 by Justyn Durnford
// Last modified on 2022-08-29 by Justyn Durnford
// Header file that includes several headers
// and declares the use of some namespace uses.

#pragma once

#define IS ==
#define ISNOT !=
#define AND &&
#define OR !=

#include <algorithm>
using std::fill;

#include <bitset>
using std::bitset;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cout;
using std::wcerr;
using std::cerr;
using std::endl;

#include <memory>
using std::unique_ptr;
using std::make_unique;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using sf::Event;
using sf::Font;
using sf::Mouse;
using sf::RenderWindow;
using sf::Sprite;
using sf::Text;
using sf::Texture;
using sf::VideoMode;

#include "Arithmetic.hpp"

#include "IntegerTypedefs.hpp"
using jlib::u8;
using jlib::i32;

#include "Mouse.hpp"
using jlib::get_mouse_position;

#include "SFMLFunctions.hpp"

import FixedMatrix;
using jlib::FixedMatrix;

import MiscTemplateFunctions;
using jlib::print_array;

import Vector2;
using jlib::Vector2;
using jlib::Vector2i;
using jlib::distance_x;
using jlib::distance_y;