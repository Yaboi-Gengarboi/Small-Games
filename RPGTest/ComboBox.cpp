// RPGTest
// ComboBox.cpp
// Created on 2022-11-28 by Justyn Durnford
// Last modified on 2022-12-01 by Justyn Durnford
// Source file for the ComboBox class.

#include "ComboBox.hpp"
#include "Resources.hpp"

void ComboBox::_updatePosition(float pos_x, float pos_y)
{
	sf::Vector2f pos(pos_x, pos_y);

	_mainButton.shape.setPosition(pos);
	sf::Vector2f size(_mainButton.shape.getSize());

	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].shape.setPosition(pos.x, pos.y + ((i + 1) * size.y));
}

void ComboBox::_updateElementWidth(float width)
{
	sf::Vector2f size(_mainButton.shape.getSize());

	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].shape.setSize(sf::Vector2f(width, size.y));
}

void ComboBox::_updateElementHeight(float height)
{
	sf::Vector2f size(_mainButton.shape.getSize());

	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].shape.setSize(sf::Vector2f(size.x, height));
}

void ComboBox::_updateElementSize(float width, float height)
{
	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].shape.setSize(sf::Vector2f(width, height));
}

void ComboBox::_updateIdleColor(const Color& color)
{
	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].idleColor = to_sfml(color);
}

void ComboBox::_updateHoverColor(const Color& color)
{
	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].hoverColor = to_sfml(color);
}

void ComboBox::_updatePressedColor(const Color& color)
{
	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].pressedColor = to_sfml(color);
}

void ComboBox::_updateOutlineColor(const Color& color)
{
	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].shape.setOutlineColor(to_sfml(color));
}

FloatRect ComboBox::_getElementBounds(size_t index)
{
	FloatRect bounds(_mainButton.shape.getGlobalBounds());
	bounds.vertex.y += bounds.height * (index + 1);

	return bounds;
}

ComboBox::ComboBox()
{
	_mainButton = Button();
	_activeElementIndex = -1;
	_showElements = false;
}

ComboBox::ComboBox(float pos_x, float pos_y, float width, float height, const string& str)
{
	_mainButton = Button(FloatRect(pos_x, pos_y, width, height), str);
	_activeElementIndex = -1;
	_showElements = false;
}

ComboBox::ComboBox(const Vector2f& new_position, const Vector2f& new_element_size, const string& str)
{
	_mainButton = Button(FloatRect(new_position, new_element_size), str);
	_activeElementIndex = -1;
	_showElements = false;
}

Vector2f ComboBox::getPosition() const
{
	return _mainButton.shape.getPosition();
}

void ComboBox::setPosition(float pos_x, float pos_y)
{
	_updatePosition(pos_x, pos_y);
}

void ComboBox::setPosition(const Vector2f& new_position)
{
	_updatePosition(new_position.x, new_position.y);
}

float ComboBox::getElementWidth() const
{
	return _mainButton.shape.getSize().x;
}

float ComboBox::getElementHeight() const
{
	return _mainButton.shape.getSize().y;
}

Vector2f ComboBox::getElementSize() const
{
	return _mainButton.shape.getSize();
}

void ComboBox::setElementWidth(float width)
{
	_updateElementWidth(width);
}

void ComboBox::setElementHeight(float height)
{
	_updateElementHeight(height);
}

void ComboBox::setElementSize(float width, float height)
{
	_updateElementSize(width, height);
}

void ComboBox::setElementSize(const Vector2f& new_size)
{
	_updateElementSize(new_size.x, new_size.y);
}

void ComboBox::setElementIdleColor(const Color& color)
{
	sf::Color new_color = to_sfml(color);

	_mainButton.idleColor = new_color;

	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].idleColor = new_color;
}

void ComboBox::setElementHoverColor(const Color& color)
{
	sf::Color new_color = to_sfml(color);

	_mainButton.hoverColor = new_color;

	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].hoverColor = new_color;
}

void ComboBox::setElementPressedColor(const Color& color)
{
	sf::Color new_color = to_sfml(color);

	_mainButton.pressedColor = new_color;

	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].pressedColor = new_color;
}

void ComboBox::setElementOutlineColor(const Color& color)
{
	sf::Color new_color = to_sfml(color);

	_mainButton.shape.setOutlineColor(new_color);

	for (size_t i = 0; i < _elements.size(); ++i)
		_elements[i].shape.setOutlineColor(new_color);
}

void ComboBox::addElement()
{
	_elements.push_back(Button(_getElementBounds(_elements.size()), "Element " + to_string(_elements.size() + 1)));
}

void ComboBox::addElement(const Font& new_font, const Text& new_text, const Color& new_idleColor, 
						  const Color& new_hoverColor, const Color& new_pressedColor)
{
	_elements.push_back(Button(_getElementBounds(_elements.size()), new_font, new_text, new_idleColor, new_hoverColor, new_pressedColor));
}

void ComboBox::setElement(size_t index, const Font& new_font, const Text& new_text, const Color& new_idleColor,
						  const Color& new_hoverColor, const Color& new_pressedColor)
{
	_elements[index] = Button(_getElementBounds(_elements.size()), new_font, new_text, new_idleColor, new_hoverColor, new_pressedColor);
}

vector<Button>::iterator ComboBox::getActiveElement()
{
	return _elements.begin() + _activeElementIndex;
}

vector<Button>::const_iterator ComboBox::getActiveElement() const
{
	return _elements.cbegin() + _activeElementIndex;
}

void ComboBox::setActiveElement(size_t index)
{
	_activeElementIndex = index;

	_mainButton.setString(_elements[_activeElementIndex].text.getString());
}

void ComboBox::update(Duration dt, InputManager& inputManager)
{
	_mainButton.update(dt, inputManager);

	if (_showElements)
	{
		if (_mainButton.state == Button::State::RELEASED)
		{
			_showElements = false;
		}
		else
		{
			for (size_t i = 0; i < _elements.size(); ++i)
			{
				_elements[i].update(dt, inputManager);

				if (_elements[i].state == Button::State::RELEASED)
				{
					setActiveElement(i);
					_showElements = false;
				}
			}
		}
	}
	else
	{
		if (_mainButton.state == Button::State::RELEASED)
		{
			_showElements = true;
		}
	}
}

void ComboBox::render(RenderWindow& window)
{
	_mainButton.render(window);

	if (_showElements)
	{
		for (size_t i = 0; i < _elements.size(); ++i)
			_elements[i].render(window);
	}
}