// RPGTest
// Button.hpp
// Created on 2022-11-19 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Header file for the Button class.

#pragma once

#include "Namespace.hpp"
#include "InputManager.hpp"

class Button
{
	public:

	enum State : u8
	{
		IDLE     = 0,
		HOVER    = 1,
		PRESSED  = 2,
		RELEASED = 3
	};

	RectangleShape shape;
	const Font& font;
	Text text;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressedColor;
	State state;
	State lastState;

	// Default constructor.
	Button();

	// Bounds constructor.
	Button(const FloatRect& bounds);

	// Bounds and string constructor.
	Button(const FloatRect& bounds, const string& str);

	// Primary constructor.
	Button(const FloatRect& bounds, const Font& new_font, const Text& new_text,
		   const Color& new_idleColor, const Color& new_hoverColor, const Color& new_pressedColor);

	// 
	Button(const Button& other);

	// 
	Button(Button&& other);

	// 
	~Button() = default;

	// 
	Button& operator = (const Button& other);

	// 
	Button& operator = (Button&& other);

	// 
	void setPosition(float pos_x, float pos_y);

	// 
	void setPosition(const Vector2f& pos);

	// 
	void setSize(float width, float height);

	// 
	void setSize(const Vector2f& size);

	// 
	void setString(const string& str);

	// 
	void setFillColors(const Color& new_idleColor, const Color& new_hoverColor, const Color& new_pressedColor);

	// 
	void update(Duration dt, InputManager& inputManager);

	// 
	void render(RenderWindow& window);
};