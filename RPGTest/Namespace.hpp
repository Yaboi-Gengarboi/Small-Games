#pragma once

#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4267 ) 

#include <SFML/Graphics/Font.hpp>
using sf::Font;

#include <SFML/Graphics/RectangleShape.hpp>
using sf::RectangleShape;

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include <SFML/Graphics/Sprite.hpp>
using sf::Sprite;

#include <SFML/Graphics/Text.hpp>
using sf::Text;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include <SFML/Graphics/View.hpp>
using sf::View;

#include <SFML/Window/Event.hpp>
using sf::Event;

#include <SFML/Window/Keyboard.hpp>
using sf::Keyboard;

#include <SFML/Window/Mouse.hpp>
using sf::Mouse;

#include "AnimatedSprite.hpp"
using jlib::AnimatedSprite;

#include "Chance.hpp"
using jlib::rand_u16;

#include "Color.hpp"
using jlib::Color;

#include "Direction.hpp"
using jlib::Direction;

#include "InputBuffer.hpp"
using jlib::InputBuffer;

#include "IntegerTypedefs.hpp"
using jlib::i32;
using jlib::u8;
using jlib::u16;
using jlib::u32;

#include "Gamepad.hpp"
using jlib::Gamepad;

#include "Time.hpp"
using jlib::Clock;
using jlib::Date;
using jlib::Duration;
using jlib::Time;
using jlib::TimePoint;

#include <algorithm>
using std::find;
using std::max;
using std::min;
using std::shift_right;

#include <array>
using std::array;

#include <chrono>
using std::chrono::seconds;

#include <cmath>
using std::fabsf;
using std::floorf;
using std::fmodf;
using std::lround;

#include <cstddef>
using std::ptrdiff_t;
using std::size_t;

#include <filesystem>
using std::filesystem::path;
using std::filesystem::current_path;
using std::filesystem::exists;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <functional>
using std::function;

#include <iostream>
using std::cout;
using std::cerr;
using std::wcout;
using std::wcerr;

#include <memory>
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;

#include <numeric>
using std::midpoint;

#include <stack>
using std::stack;

#include <string>
using std::string;
using std::wstring;
using std::getline;
using std::stoi;
using std::to_string;
using std::to_wstring;

#include <thread>
using std::thread;
using std::this_thread::sleep_for;

#include <unordered_map>
using std::unordered_map;

#include <vector>
using std::vector;

import Array;
using jlib::Array;

import Clamp;
using jlib::clamp;
using jlib::clamp_max;
using jlib::clamp_min;

import Matrix;
using jlib::Matrix;

import MiscTemplateFunctions;
using jlib::are_all_equal_to;
using jlib::print_array;

import Ptr;
using jlib::Ptr;

import Rect;
using jlib::FloatRect;
using jlib::intersection;

import SFML_JLIB;
using jlib::copy_data;
using jlib::contains;
using jlib::to_jlib;
using jlib::to_sfml;

import Vector2;
using jlib::Vector2f;
using jlib::Vector2i;
using jlib::Vector2uz;
using jlib::to_string;