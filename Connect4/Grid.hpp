// Connect4
// Grid.hpp
// Created on 2022-03-23 by Justyn Durnford
// Last modified on 2022-08-15 by Justyn Durnford
// Header file for the Grid class.

#pragma once

#include "Define.hpp"

// The game's grid will be filled with tokens.
// All of the tokens are "Empty" (NONE) by default.
// Player 1 will place RED tokens while player 2
// will place YELLOW tokens.
enum Token : u8
{
	NONE = 0,
	RED = 1,
	YELLOW = 2
};

// 
class Grid
{
	// 
	constexpr char _getTokenCharacter(Token token) const;

	FixedMatrix<Token, 6, 7> _data;

	public:

	// 
	Grid();

	// 
	size_t rowCount() const noexcept;

	// 
	size_t columnCount() const noexcept;

	// 
	size_t size() const noexcept;

	// 
	Token getToken(size_t index) const;

	// 
	Token getToken(size_t row, size_t col) const;

	// 
	Token getToken(const Vector2i& pos) const;

	// 
	void setToken(Token token, size_t row, size_t col);

	// 
	void setToken(Token token, const Vector2i& pos);

	// 
	bool isColumnFull(size_t col) const;

	// 
	size_t currentRow(size_t col) const;

	// 
	bool dropToken(Token token, size_t col);

	// 
	void clear();

	// 
	void print() const;
};