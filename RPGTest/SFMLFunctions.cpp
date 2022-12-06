// Connect4
// SFMLFunctions.cpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// 

#include "SFMLFunctions.hpp"

bool create_font(Font& font, const string& filedir)
{
	return font.loadFromFile(filedir);
}

bool create_font(Font& font, const path& filedir)
{
	return font.loadFromFile(filedir.string());
}

void create_text(Text& text, const sf::Vector2f& pos, const sf::String& str, const Font& font, u32 character_size,
	u32 style, const sf::Color& fill_color, const sf::Color& outline_color, float outline_thickness)
{
	text.setString(str);
	text.setFont(font);
	text.setCharacterSize(character_size);
	text.setPosition(pos);
	text.setStyle(style);
	text.setFillColor(fill_color);
	text.setOutlineColor(outline_color);
	text.setOutlineThickness(outline_thickness);
}

void center_text(Text& text, const FloatRect& bounds)
{
	text.setOrigin(get_size(text.getGlobalBounds()) / 2.0f + get_position(text.getLocalBounds()));
	text.setPosition(to_sfml(bounds.vertex + (bounds.dimensions() / 2.0f)));
}

bool create_texture(Texture& texture, const string& filedir)
{
	return texture.loadFromFile(filedir);
}

bool create_texture(Texture& texture, const path& filedir)
{
	return texture.loadFromFile(filedir.string());
}

sf::Vector2f get_size(const sf::FloatRect& rect)
{
	return sf::Vector2f(rect.width, rect.height);
}

sf::Vector2f get_position(const sf::FloatRect& rect)
{
	return sf::Vector2f(rect.left, rect.top);
}