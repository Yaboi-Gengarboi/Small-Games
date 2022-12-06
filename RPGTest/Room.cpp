// RPGTest
// Room.cpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-11-16 by Justyn Durnford
// Source file for the Room class.

#include "GameConstants.hpp"
#include "Room.hpp"
#include "SFMLFunctions.hpp"

Room::Room(u16 new_id, const path& folder) : IDObject(new_id, "")
{
	#ifdef _DEBUG
	cout << "Loading room data...\n";
	#endif // #ifdef _DEBUG

	path datafile(folder / "rooms" / to_wstring(new_id) / "data.txt");

	if (!exists(datafile))
		loadFail(datafile, L"Could not locate file: " + datafile.wstring());

	ifstream fin(datafile);
	string line;
	int rows = 0, cols = 0;

	try
	{
		if (!getline(fin, line))
			throw;

		_name = line;

		#ifdef _DEBUG
		cout << _name << '\n';
		#endif // #ifdef _DEBUG
	}
	catch (...)
	{
		loadFail(datafile, L"Could not read name of Room : " + to_wstring(new_id));
	}

	try
	{
		if (!getline(fin, line))
			throw;

		rows = stoi(line);

		#ifdef _DEBUG
		cout << to_string(rows) << '\n';
		#endif // #ifdef _DEBUG
	}
	catch (...)
	{
		loadFail(datafile, L"Could not read rows of Room : " + to_wstring(new_id));
	}

	try
	{
		if (!getline(fin, line))
			throw;

		cols = stoi(line);

		#ifdef _DEBUG
		cout << to_string(cols) << '\n';
		#endif // #ifdef _DEBUG
	}
	catch (...)
	{
		loadFail(datafile, L"Could not read columns of Room : " + to_wstring(new_id));
	}

	try
	{
		if (!getline(fin, line))
			throw;

		startPos = jlib::str_to_vec2_f32(line);

		#ifdef _DEBUG
		cout << startPos << "\n\n";
		#endif // #ifdef _DEBUG
	}
	catch (...)
	{
		loadFail(datafile, L"Could not read start position of Room : " + to_wstring(new_id));
	}

	collision = Matrix<u8>(rows, cols);

	u8 tile = 0;

	for (size_t row_i = 0; row_i < collision.rowCount(); ++row_i)
	{
		for (size_t col_i = 0; col_i < collision.colCount(); ++col_i)
		{
			fin >> tile;
			if (fin.fail())
				loadFail(datafile, L"Could not read tile(" + to_wstring(row_i) + to_wstring(col_i) + L" from Room : " + to_wstring(new_id));

			#ifdef _DEBUG
			cout << to_string(tile - 48) << ' ';
			#endif // #ifdef _DEBUG

			collision(row_i, col_i) = tile - 48;
		}

		#ifdef _DEBUG
		cout  << '\n';
		#endif // #ifdef _DEBUG
	}

	try
	{

	}
	catch (...)
	{

	}

	string texturefile(folder.string() + "\\rooms\\" + to_string(new_id) + "\\texture.png");
	if (!exists(texturefile))
	{
		cerr << "ERROR: Could not locate file: " << texturefile << '\n';
		exit(1);
	}

	create_texture(texture, texturefile);
	sprite.setTexture(texture);
	sprite.setScale(SCALE, SCALE);
}

Room::Room(Room&& other) noexcept
{
	texture = other.texture;
	sprite.setTexture(texture);
	sprite.setScale(SCALE, SCALE);
	collision.swapWith(other.collision);
	startPos = other.startPos;
}

Room& Room::operator = (Room&& other) noexcept
{
	texture = other.texture;
	sprite.setTexture(texture);
	sprite.setScale(SCALE, SCALE);
	collision.swapWith(other.collision);
	startPos = other.startPos;
	return *this;
}

void Room::loadFail(const path& filepath, const wstring& message)
{
	wcerr << L"Error encountered while reading from file: " << filepath << L'\n';
	wcerr << message << L'\n';
	exit(1);
}

Vector2uz Room::relativeTile(float pos_x, float pos_y) const
{
	return Vector2uz(static_cast<size_t>(pos_x / SCALE / TILE_LENGTH), static_cast<size_t>(pos_y / SCALE / TILE_LENGTH));
}

Vector2uz Room::relativeTile(const Vector2f& pos) const
{
	return relativeTile(pos.x, pos.y);
}

Collision Room::getTileCollision(float pos_x, float pos_y) const
{
	return Collision(collision(relativeTile(pos_x, pos_y)));
}

Collision Room::getTileCollision(const Vector2f& pos) const
{
	return getTileCollision(pos.x, pos.y);
}

unordered_map<u16, Room> room_arr;

bool is_tile_empty(Collision collision, TravelMethod travel_method)
{
	switch (travel_method)
	{
		case TravelMethod::WALKING:

			switch (collision)
			{
				case Collision::EMPTY:
					return true;
				break;

				case Collision::LOADZONE:
					return true;
				break;

				case Collision::SOLID:
					return false;
				break;

				case Collision::WATER:
					return false;
				break;

				default: break;
			}

		break;

		case TravelMethod::RUNNING:

			switch (collision)
			{
				case Collision::EMPTY:
				return true;
				break;

				case Collision::LOADZONE:
				return true;
				break;

				case Collision::SOLID:
				return false;
				break;

				case Collision::WATER:
				return false;
				break;

				default: break;
			}

		break;

		default: break;
	}

	return false;
}

bool is_tile_solid(Collision collision, TravelMethod travel_method)
{
	return !is_tile_empty(collision, travel_method);
}

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