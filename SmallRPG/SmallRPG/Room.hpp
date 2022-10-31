// SmallRPG
// Room.hpp
// Created on 2022-07-27 by Justyn Durnford
// Last modified on 2022-08-01 by Justyn Durnford
// Header file for the Room class.

#pragma once

#include "Collision.hpp"
#include "IDObject.hpp"

#include <SFML/Graphics/Sprite.hpp>
using sf::Sprite;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

#include <unordered_map>
using std::unordered_map;

import Matrix;
using jlib::Matrix;

import Ptr;
using jlib::Ptr;

import Vector2;
using jlib::Vector2u;

class Room : public IDObject
{
	public:

	Texture texture;
	Sprite sprite;
	Matrix<u8> collision;
	Vector2u startPos;

	// Default constructor.
	Room() = default;

	// Constructor.
	Room(u16 new_id, const path& folder);

	// Move constructor.
	Room(Room&& other) noexcept;

	// Move assignment operator.
	Room& operator = (Room&& other) noexcept;
};

extern unordered_map<u16, Room> room_arr;
bool load_room(u16 id, const path& folder);
void unload_room(u16 id);