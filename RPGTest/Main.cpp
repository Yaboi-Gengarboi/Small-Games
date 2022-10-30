// RPGTest
// Main.cpp
// Created on 2022-09-28 by Justyn Durnford
// Last modified on 2022-10-22 by Justyn Durnford
// Main file for the RPGTest project.

#include "Angle.hpp"
#include "Resources.hpp"
#include "RPGGame.hpp"
#include "Room.hpp"
#include "SFMLFunctions.hpp"

#include <iostream>

import Ptr;
using jlib::Ptr;

import Vector2;
using jlib::Vector2f;

//class TestObject : public IDObject
//{
//	private:
//
//	std::string _desc;
//
//	public:
//
//	TestObject() = default;
//
//	TestObject(jlib::u16 new_id, const std::string& new_name, const std::string& new_desc) 
//		: IDObject(new_id, new_name), _desc(new_desc) {}
//
//	constexpr const std::string& getDesc() const noexcept
//	{
//		return _desc;
//	}
//};

template <typename T>
void println(const T& value)
{
	std::cout << value << '\n';
}

void println(const std::string& str)
{
	std::cout << str << '\n';
}

int main(int argc, char** argv)
{
	if (!create_font(consolas_font, L"data\\fonts\\times.ttf"))
		return -1;

	RPGGame game;
	game.run();

	return 0;
}