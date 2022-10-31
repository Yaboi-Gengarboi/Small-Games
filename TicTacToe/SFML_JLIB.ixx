// JLibrary
// SFML_JLIB.ixx
// Created on 2022-01-09 by Justyn Durnford
// Last modified on 2022-03-09 by Justyn Durnford
// Module file defining several functions to convert 
// and copy data between SFML and JLIB code.

module;

#ifdef INCLUDE_SFML

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Arithmetic.hpp"

#include <cmath>

#endif // #ifdef INCLUDE_SFML

export module SFML_JLIB;

import Vector2;

#ifdef INCLUDE_SFML

export namespace jlib
{
	template <arithmetic T>
	sf::Vector2<T> to_sfml(const Vector2<T>& v)
	{
		return sf::Vector2<T>(v.x, v.y);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	template <arithmetic T>
	Vector2<T> to_jlib(const sf::Vector2<T>& v)
	{
		return Vector2<T>(v.x, v.y);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	template <arithmetic T>
	void copy_data(const jlib::Vector2<T>& from, sf::Vector2<T>& to)
	{
		to.x = from.x;
		to.y = from.y;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	template <arithmetic T>
	void copy_data(const sf::Vector2<T>& from, jlib::Vector2<T>& to)
	{
		to.x = from.x;
		to.y = from.y;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	template <arithmetic T>
	constexpr float magnitude(const sf::Vector2<T>& v)
	{
		return std::sqrtf(std::powf(static_cast<float>(v.x), 2.0f) + std::powf(static_cast<float>(v.y), 2.0f));
	}

	template <arithmetic T>
	constexpr float magnitude(const sf::Vector3<T>& v)
	{
		return std::sqrtf(std::powf(static_cast<float>(v.x), 2.0f) + std::powf(static_cast<float>(v.y), 2.0f) + std::powf(static_cast<float>(v.z), 2.0f));
	}

	template <arithmetic T>
	sf::Vector2<T> unit_vector(const sf::Vector2<T>& v)
	{
		constexpr float m = magnitude(v);
		return sf::Vector2<float>(v.x / m, v.y / m);
	}

	template <arithmetic T>
	sf::Vector3<T> unit_vector(const sf::Vector3<T>& v)
	{
		constexpr float m = magnitude(v);
		return sf::Vector3<float>(v.x / m, v.y / m, v.z / m);
	}

	template <arithmetic T>
	std::string to_string(const sf::Vector2<T>& v)
	{
		return '<' + std::to_string(v.x) + ", " + std::to_string(v.y) + '>';
	}

	template <arithmetic T>
	std::string to_string(const sf::Vector3<T>& v)
	{
		return '<' + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + '>';
	}

	template <arithmetic T>
	std::wstring to_wstring(const sf::Vector2<T>& v)
	{
		return L'<' + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L'>';
	}

	template <arithmetic T>
	std::wstring to_wstring(const sf::Vector3<T>& v)
	{
		return L'<' + std::to_wstring(v.x) + L", " + std::to_wstring(v.y) + L", " + std::to_wstring(v.z) + L'>';
	}
}

#endif // #ifdef INCLUDE_SFML