#pragma once

#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4267 ) 

#ifndef NOMINMAX
#define NOMINMAX
#endif // #ifndef NOMINMAX

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/Graphics/Sprite.hpp>
using sf::Sprite;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include "AnimatedSprite.hpp"
using jlib::AnimatedSprite;

#include "Direction.hpp"
using jlib::Direction;

#include "IntegerTypedefs.hpp"
using jlib::i32;
using jlib::u8;
using jlib::u16;
using jlib::u32;

#include "Time.hpp"
using jlib::Duration;

#include <algorithm>
using std::max;
using std::min;

#include <array>
using std::array;

#include <cmath>
using std::floorf;
using std::fmodf;
using std::lround;

#include <cstddef>
using std::size_t;

#include <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>
using std::cout;
using std::wcout;
using std::wcerr;

#include <string>
using std::string;
using std::wstring;
using std::getline;
using std::stoi;
using std::to_string;
using std::to_wstring;

#include <thread>
using std::thread;

#include <unordered_map>
using std::unordered_map;

#include <vector>
using std::vector;

import Clamp;
using jlib::clamp;
using jlib::clamp_max;
using jlib::clamp_min;

import Matrix;
using jlib::Matrix;

import Ptr;
using jlib::Ptr;

import Rect;
using jlib::FloatRect;
using jlib::intersection;

import Vector2;
using jlib::Vector2f;
using jlib::Vector2uz;
using jlib::to_string;