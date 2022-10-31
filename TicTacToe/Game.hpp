// TicTacToe
// Game.hpp
// Created on 2022-02-07 by Justyn Durnford
// Last modified on 2022-03-11 by Justyn Durnford
// Header file for the Game class.

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using sf::Event;
using sf::Font;
using sf::Mouse;
using sf::RenderWindow;
using sf::Sprite;
using sf::Text;
using sf::Texture;
using sf::VideoMode;

#include <array>
using std::array;

#include <bitset>
using std::bitset;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::getline;
using std::stoul;

import FixedMatrix;
using jlib::FixedMatrix;

import Vector2;
using jlib::Vector2i;
using jlib::distance_x;
using jlib::distance_y;

const Vector2i origin(0, 0);

class Game
{
	RenderWindow _window;
	Texture _boardTexture;
	Texture _xTexture;
	Texture _oTexture;
	Sprite _boardSprite;
	FixedMatrix<Sprite, 3, 3> _xSprites;
	FixedMatrix<Sprite, 3, 3> _oSprites;
	Text _gameText;
	Event _event;
	Vector2i _mousePos;
	FixedMatrix<char, 3, 3> _board;
	bitset<8> _flags;
	unsigned int _row, _col;

	// Flags:
	// - _flags[0]: isGameRunning?
	// - _flags[1]: isPlayer1Turn?
	// - _flags[2]: hasPlayer1Won?
	// - _flags[3]: hasPlayer2Won?
	// - _flags[4]: shouldProgress?
	// - _flags[5]: mouseInput?

	#ifdef _DEBUG

		// 
		void printBoard();

	#endif // #ifdef _DEBUG

	// 
	void processEvents();

	// 
	void update();

	// 
	void render();

	// 
	void clearBoard();

	// 
	void promptContinue();

	// 
	bool isSpaceEmpty(unsigned int row, unsigned int col) const;

	// 
	void checkRow(unsigned int row);

	// 
	void checkColumn(unsigned int col);

	// 
	void checkDownRightDiagonal();

	// 
	void checkUpRightDiagonal();

	public:

	// 
	Game();

	// 
	bool isGameRunning() const;

	// 
	bool isPlayer1Turn() const;

	// 
	bool hasPlayer1Won() const;

	// 
	bool hasPlayer2Won() const;
	
	// 
	bool isBoardFull() const;

	// 
	bool shouldProgress() const;

	// 
	bool mouseInput() const;

	// 
	void run();
};