// RPGTest
// Room.hpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-10-28 by Justyn Durnford
// Header file for the Room class.

#pragma once

#include "IntegerTypedefs.hpp"
using jlib::u8;
using jlib::u16;

#include "Collision.hpp"
#include "IDObject.hpp"

#include <SFML/Graphics/Sprite.hpp>
using sf::Sprite;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

#include <string>
using std::string;
using std::wstring;

#include <unordered_map>
using std::unordered_map;

import Matrix;
using jlib::Matrix;

import Ptr;
using jlib::Ptr;

import Vector2;
using jlib::Vector2f;
using jlib::Vector2uz;

// 
class Room : public IDObject
{
	public:

	Texture texture;
	Sprite sprite;
	Matrix<u8> collision;
	Vector2f startPos;

	// Default constructor.
	Room() = default;

	// Constructor.
	Room(u16 new_id, const path& folder);

	// Move constructor.
	Room(Room&& other) noexcept;

	// Move assignment operator.
	Room& operator = (Room&& other) noexcept;

	// 
	static void loadFail(const path& filepath, const wstring& message);

	// 
	Vector2uz relativeTile(float pos_x, float pos_y) const;

	// 
	Vector2uz relativeTile(const Vector2f& pos) const;

	// 
	Collision getTileCollision(float pos_x, float pos_y) const;

	// 
	Collision getTileCollision(const Vector2f& pos) const;
};

extern unordered_map<u16, Room> room_arr;

// 
bool load_room(u16 id, const path& folder);

// 
void unload_room(u16 id);