// RPGTest
// SFMLFunctions.hpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-12-05 by Justyn Durnford
// 

#pragma once

#include "Namespace.hpp"

bool create_font(Font& font, const string& filedir);

bool create_font(Font& font, const path& filedir);

void create_text(Text& text, const sf::Vector2f& pos, const sf::String& str, const Font& font, u32 character_size,
	u32 style, const sf::Color& fill_color, const sf::Color& outline_color, float outline_thickness);

void center_text(Text& text, const FloatRect& bounds);

bool create_texture(Texture& texture, const string& filedir);

bool create_texture(Texture& texture, const path& filedir);

sf::Vector2f get_size(const sf::FloatRect& rect);

sf::Vector2f get_position(const sf::FloatRect& rect);