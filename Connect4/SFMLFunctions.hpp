// Connect4
// SFMLFunctions.hpp
// Created on 2022-03-10 by Justyn Durnford
// Last modified on 2022-08-27 by Justyn Durnford
// Header file that declares several SFML related functions.

#pragma once

#include "IntegerTypedefs.hpp"
using jlib::u32;

#include <SFML/Graphics/Font.hpp>
using sf::Font;

#include <SFML/Graphics/Text.hpp>
using sf::Text;

#include <SFML/Graphics/Texture.hpp>
using sf::Texture;

#include <filesystem>
using std::filesystem::path;

// 
bool create_font(Font& font, const path& filedir);

void create_text(Text& text, const sf::Vector2f& pos, const sf::String& str, const Font& font, u32 character_size,
				 u32 style, const sf::Color& fill_color, const sf::Color& outline_color, float outline_thickness);

// 
bool create_texture(Texture& texture, const path& filedir);