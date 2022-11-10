// RPGTest
// Room.hpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-11-09 by Justyn Durnford
// Header file for the Room class.

#pragma once

#include "Namespace.hpp"

#include "IDObject.hpp"

enum Collision : u8
{
	EMPTY = 0,
	LOADZONE = 1,
	SOLID = 2,
	WATER = 3
};

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