// RPGTest
// ComboBox.hpp
// Created on 2022-11-28 by Justyn Durnford
// Last modified on 2022-12-01 by Justyn Durnford
// Header file for the ComboBox class.

#pragma once

#include "Namespace.hpp"
#include "Button.hpp"
#include "InputManager.hpp"

class ComboBox
{
	Button _mainButton;
	vector<Button> _elements;
	i32 _activeElementIndex;
	bool _showElements;

	// Updates the position of every element of the ComboBox.
	void _updatePosition(float pos_x, float pos_y);

	// Updates the width of every element of the ComboBox.
	void _updateElementWidth(float width);

	// Updates the height of every element of the ComboBox.
	void _updateElementHeight(float height);

	// Updates the size of every element of the ComboBox.
	void _updateElementSize(float width, float height);

	// Updates the idle color of every element of the ComboBox.
	void _updateIdleColor(const Color& color);

	// Updates the hover color of every element of the ComboBox.
	void _updateHoverColor(const Color& color);

	// Updates the pressed color of every element of the ComboBox.
	void _updatePressedColor(const Color& color);

	// Updates the outline color of every element of the ComboBox.
	void _updateOutlineColor(const Color& color);

	// Returns the bounds of the given element.
	FloatRect _getElementBounds(size_t index);

	public:

	// Default constructor.
	ComboBox();

	// Primary constructor.
	ComboBox(float pos_x, float pos_y, float width, float height, const string& str = "Select");

	// Secondary constructor.
	ComboBox(const Vector2f& new_position, const Vector2f& new_element_size, const string& str = "Select");

	// Returns the position of the ComboBox.
	Vector2f getPosition() const;

	// Sets the position of the ComboBox to the new position.
	void setPosition(float pos_x, float pos_y);

	// Sets the position of the ComboBox to the new position.
	void setPosition(const Vector2f& new_position);

	// Returns the width of the elements.
	float getElementWidth() const;

	// Returns the height of the elements.
	float getElementHeight() const;

	// Returns the size of the elements.
	Vector2f getElementSize() const;

	// Sets the width of the elements to the new width.
	void setElementWidth(float width);

	// Sets the width of the elements to the new height.
	void setElementHeight(float height);

	// Sets the size of the elements to the new width and height.
	void setElementSize(float width, float height);

	// Sets the size of the elements to the new width and height.
	void setElementSize(const Vector2f& new_size);

	// Sets the idle color of the elements to the new color.
	void setElementIdleColor(const Color& color);

	// Sets the hover color of the elements to the new color.
	void setElementHoverColor(const Color& color);

	// Sets the pressed color of the elements to the new color.
	void setElementPressedColor(const Color& color);

	// Sets the outline color of the elements to the new color.
	void setElementOutlineColor(const Color& color);

	// 
	void addElement();

	// 
	void addElement(const Font& new_font, const Text& new_text, const Color& new_idleColor, 
					const Color& new_hoverColor, const Color& new_pressedColor);

	// 
	void setElement(size_t index, const Font& new_font, const Text& new_text, const Color& new_idleColor, 
					const Color& new_hoverColor, const Color& new_pressedColor);

	// 
	vector<Button>::iterator getActiveElement();

	// 
	vector<Button>::const_iterator getActiveElement() const;

	// 
	void setActiveElement(size_t index);

	// 
	void update(Duration dt, InputManager& inputManager);

	// 
	void render(RenderWindow& window);
};