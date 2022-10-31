// TicTacToe
// SFMLFunctions.hpp
// Created on 2022-03-10 by Justyn Durnford
// Last modified on 2022-03-10 by Justyn Durnford
// Header file that declares several SFML related functions.

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using sf::Texture;

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

//
void load_texture(Texture& texture, const string& filedir);