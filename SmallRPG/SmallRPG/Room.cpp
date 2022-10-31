// SmallRPG
// Room.cpp
// Created on 2022-07-27 by Justyn Durnford
// Last modified on 2022-07-27 by Justyn Durnford
// Source for the Room class.

#include "Room.hpp"

#include "FileManager.hpp"
using jlib::FileManager; 

#include "SFMLFunctions.hpp"

#include <iostream>
using std::cerr;
using std::wcout;
using std::wcerr;

#include <string>
using std::string;
using std::to_string;
using std::to_wstring;

Room::Room(u16 new_id, const path& folder) : IDObject(new_id, "")
{
	path datafile(folder / to_wstring(new_id) / "data.txt");

	if (!exists(datafile))
	{
		wcerr << L"ERROR: Could not locate file: " << datafile << L'\n';
		exit(1);
	}
	else
	{
		FileManager fileman(folder / to_wstring(new_id) / "data.txt");

		int rows, cols;

		name = fileman.readLine();
		fileman >> rows;
		fileman >> cols;
		fileman >> startPos.x;
		fileman >> startPos.y;

		collision = Matrix<u8>(rows, cols);

		string texturefile("data\\rooms\\" + to_string(new_id) + "\\texture.png");

		if (!exists(texturefile))
		{
			cerr << "ERROR: Could not locate file: " << texturefile << '\n';
			exit(1);
		}
		else
		{
			create_texture(texture, texturefile);
			sprite.setTexture(texture);
			sprite.setScale(2.0f, 2.0f);

			for (size_t row_i = 0; row_i < collision.rowCount(); ++row_i)
			{
				for (size_t col_i = 0; col_i < collision.colCount(); ++col_i)
					collision(row_i, col_i) = fileman.get<u8>() - 48;
			}
		}
	}
}

Room::Room(Room&& other) noexcept
{
	texture = other.texture;
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);
	collision.swapWith(other.collision);
	startPos = other.startPos;
}

Room& Room::operator = (Room&& other) noexcept
{
	texture = other.texture;
	sprite.setTexture(texture);
	sprite.setScale(2.0f, 2.0f);
	collision.swapWith(other.collision);
	startPos = other.startPos;
	return *this;
}

unordered_map<u16, Room> room_arr;

bool load_room(u16 id, const path& folder)
{
	try
	{
		if (room_arr.find(id) == room_arr.end())
		{
			room_arr[id] = Room(id, folder);
			return true;
		}
		else if (room_arr.find(id) != room_arr.end())
			return true;
	}
	catch (...) {}

	return false;
}

void unload_room(u16 id)
{
	unordered_map<u16, Room>::iterator iter = room_arr.find(id);

	if (iter != room_arr.end())
		room_arr.erase(iter);
}