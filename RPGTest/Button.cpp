// RPGTest
// Button.cpp
// Created on 2022-11-19 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// Source file for the Button class.

#include "Button.hpp"
#include "Resources.hpp"
#include "SFMLFunctions.hpp"

Button::Button() : font(resources->consolas_font)
{
	text.setString("New Button");
	state = State::IDLE;
	lastState = State::IDLE;
}

Button::Button(const FloatRect& bounds) 
	: shape(to_sfml(bounds.dimensions())), font(resources->consolas_font), text("New Button", font, 30u)
{
	shape.setPosition(bounds.vertex.x, bounds.vertex.y);

	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3.0f);

	center_text(text, bounds);

	idleColor = to_sfml(Color::Gray);
	hoverColor = to_sfml(Color::DarkGray);
	pressedColor = to_sfml(Color::LightGray);

	shape.setFillColor(idleColor);

	state = State::IDLE;
	lastState = State::IDLE;
}

Button::Button(const FloatRect& bounds, const string& str) 
	: shape(to_sfml(bounds.dimensions())), font(resources->consolas_font), text(str, font, 30u)
{
	shape.setPosition(bounds.vertex.x, bounds.vertex.y);

	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3.0f);

	center_text(text, bounds);

	idleColor = to_sfml(Color::Gray);
	hoverColor = to_sfml(Color::LightGray);
	pressedColor = to_sfml(Color::DarkGray);

	shape.setFillColor(idleColor);

	state = State::IDLE;
	lastState = State::IDLE;
}

Button::Button(const FloatRect& bounds, const Font& new_font, const Text& new_text,
			   const Color& new_idleColor, const Color& new_hoverColor, const Color& new_pressedColor)
	: shape(to_sfml(bounds.dimensions())), font(new_font), text(new_text)
{
	shape.setPosition(bounds.vertex.x, bounds.vertex.y);

	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3.0f);

	center_text(text, bounds);

	idleColor = to_sfml(new_idleColor);
	hoverColor = to_sfml(new_hoverColor);
	pressedColor = to_sfml(new_pressedColor);

	shape.setFillColor(idleColor);

	state = State::IDLE;
	lastState = State::IDLE;
}

Button::Button(const Button& other) : font(other.font)
{
	shape = other.shape;
	text = other.text;
	idleColor = other.idleColor;
	hoverColor = other.hoverColor;
	pressedColor = other.pressedColor;
	state = other.state;
	lastState = other.lastState;
}

Button::Button(Button&& other) : font(other.font)
{
	shape = other.shape;
	text = other.text;
	idleColor = other.idleColor;
	hoverColor = other.hoverColor;
	pressedColor = other.pressedColor;
	state = other.state;
	lastState = other.lastState;
}

Button& Button::operator = (const Button& other)
{
	shape = other.shape;
	text = other.text;
	idleColor = other.idleColor;
	hoverColor = other.hoverColor;
	pressedColor = other.pressedColor;
	state = other.state;
	lastState = other.lastState;

	return *this;
}

Button& Button::operator = (Button&& other)
{
	shape = other.shape;
	text = other.text;
	idleColor = other.idleColor;
	hoverColor = other.hoverColor;
	pressedColor = other.pressedColor;
	state = other.state;
	lastState = other.lastState;

	return *this;
}

void Button::setPosition(float pos_x, float pos_y)
{
	shape.setPosition(pos_x, pos_y);
	center_text(text, shape.getGlobalBounds());
}

void Button::setPosition(const Vector2f& pos)
{
	shape.setPosition(pos.x, pos.y);
	center_text(text, shape.getGlobalBounds());
}

void Button::setSize(float width, float height)
{
	shape.setSize(sf::Vector2f(width, height));
	center_text(text, shape.getGlobalBounds());
}

void Button::setSize(const Vector2f& size)
{
	shape.setSize(to_sfml(size));
	center_text(text, shape.getGlobalBounds());
}

void Button::setString(const string& str)
{
	text.setString(str);
	center_text(text, shape.getGlobalBounds());
}

void Button::setFillColors(const Color& new_idleColor, const Color& new_hoverColor, const Color& new_pressedColor)
{
	idleColor = to_sfml(new_idleColor);
	hoverColor = to_sfml(new_hoverColor);
	pressedColor = to_sfml(new_pressedColor);
}

void Button::update(Duration dt, InputManager& inputManager)
{
	lastState = state;

	if (contains(shape.getGlobalBounds(), inputManager.mousePosition.x, inputManager.mousePosition.y))
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			state = State::PRESSED;
			shape.setFillColor(pressedColor);
		}
		else if (lastState == Button::State::PRESSED)
		{
			state = State::RELEASED;
			shape.setFillColor(hoverColor);
		}
		else
		{
			state = State::HOVER;
			shape.setFillColor(hoverColor);
		}
	}
	else
	{
		state = State::IDLE;
		shape.setFillColor(idleColor);
	}
}

void Button::render(RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}