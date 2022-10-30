// RPGTest
// Entity.hpp
// Created on 2022-10-20 by Justyn Durnford
// Last modified on 2022-10-27 by Justyn Durnford
// Header file for the Entity class.

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
using sf::RenderWindow;

#include "Time.hpp"
using jlib::Duration;

import Vector2;
using jlib::Vector2f;

class Entity
{
	public:

	Vector2f position;
	Vector2f velocity;

	// Default constructor.
	Entity() = default;

	// 
	Entity(const Vector2f& new_position, const Vector2f& new_velocity)
		: position(new_position), velocity(new_velocity) {}

	// Virtual destructor.
	~Entity() noexcept = default;

	// 
	virtual void render(RenderWindow& window) = 0;
};