// Connect4
// Game.hpp
// Created on 2022-03-22 by Justyn Durnford
// Last modified on 2022-08-29 by Justyn Durnford
// Header file for the Game class.

#pragma once

#include "Define.hpp"
#include "Grid.hpp"

class Game
{
	private:

	// 
	void _processEvents();

	// 
	void _update();

	// 
	void _render();

	// 
	void _promptContinue();

	// 
	bool _isSpaceEmpty(size_t row, size_t col) const;

	// 
	bool _checkRow(size_t row);

	// 
	bool _checkColumn(size_t col);

	// 
	bool _checkUpRightDiagonal(size_t row, size_t col);

	// 
	bool _checkUpLeftDiagonal(size_t row, size_t col);

	// 
	void _checkDiagonals();

	Grid _grid;

	// Flags:
	// - _flags[0]: isGameRunning?
	// - _flags[1]: isPlayer1Turn?
	// - _flags[2]: isPlayer2Turn?
	// - _flags[3]: hasPlayer1Won?
	// - _flags[4]: hasPlayer2Won?
	// - _flags[5]: shouldProgress?
	// - _flags[6]: mouseInput?
	bitset<8> _flags;

	Vector2i _mousePos;

	RenderWindow _window;
	Event _event;

	Texture _gridTexture;
	Texture _tokenTexture;

	Sprite _gridSprite;
	FixedMatrix<Sprite, 6, 7> _tokenSprites;

	public:

	// 
	Game(int test_code = 0);

	// 
	bool isGameRunning() const noexcept;

	// 
	bool isPlayer1Turn() const noexcept;

	// 
	bool isPlayer2Turn() const noexcept;

	// 
	bool hasPlayer1Won() const noexcept;

	// 
	bool hasPlayer2Won() const noexcept;

	// 
	bool isBoardFull() const;

	// 
	bool shouldProgress() const noexcept;

	// 
	bool mouseInput() const noexcept;

	// 
	void run();
};