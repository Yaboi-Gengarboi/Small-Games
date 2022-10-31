// TicTacToe
// Game.cpp
// Created on 2022-02-07 by Justyn Durnford
// Last modified on 2022-03-11 by Justyn Durnford
// Source file for the Game class.

#include "Game.hpp"
#include "SFMLFunctions.hpp"

import SFML_JLIB;
using jlib::copy_data;

#ifdef _DEBUG

	void Game::printBoard()
	{
		cout << "    0 1 2\n";
	
		for (unsigned char row_i = 0; row_i < 3; ++row_i)
		{
			cout << int(row_i) << " | ";
	
			for (unsigned char col_i = 0; col_i < 3; ++col_i)
				cout << _board(row_i, col_i) << ' ';
	
			cout << "|\n";
		}
	}

#endif // #ifdef _DEBUG

void Game::processEvents()
{
	// Process events.
	while (_window.pollEvent(_event))
	{
		switch (_event.type)
		{
			// Close window: exit.
			case Event::Closed:
				_window.close();
			break;

			// Pressed Mouse button.
			case Event::MouseButtonPressed:

				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					copy_data(Mouse::getPosition(_window), _mousePos);

					#ifdef _DEBUG
						cout << _mousePos << endl;
					#endif // #ifdef _DEBUG

					_flags[5] = true;
				}
				
			break;

			default: break;
		}
	}
}

void Game::update()
{
	if (mouseInput())
	{
		_flags[5] = false;

		_col = unsigned int(float(_mousePos.x * 0.005));
		_row = unsigned int(float(_mousePos.y * 0.005));

		#ifdef _DEBUG
			cout << "Row: " << _row << "; Col: " << _col << endl;
		#endif // ifdef _DEBUG

		_flags[4] = false;
		
		if (_row < 3 && _col < 3)
		{
			if (isSpaceEmpty(_row, _col))
				_flags[4] = true;
		}

		if (shouldProgress())
		{
			if (isPlayer1Turn())
				_board(_row, _col) = 'X';
			else
				_board(_row, _col) = 'O';

			#ifdef _DEBUG
				printBoard();
			#endif // ifdef _DEBUG

			if (_flags[1])
				_flags[1] = false;
			else
				_flags[1] = true;

			for (unsigned int i = 0; i < 3; ++i)
			{
				checkRow(i);
				checkColumn(i);
			}

			checkDownRightDiagonal();
			checkUpRightDiagonal();

			_flags[4] = false;
		}
	}
}

void Game::render()
{
	// Clear screen.
	_window.clear();

	// Draw sprites.
	_window.draw(_boardSprite);

	for (int i = 0; i < 9; ++i)
	{
		if (_board[i] == 'X')
			_window.draw(_xSprites[i]);
		if (_board[i] == 'O')
			_window.draw(_oSprites[i]);
	}

	// Display the window's contents.
	_window.display();

	if (hasPlayer1Won())
	{
		cout << "Player 1 has won!" << endl;
		promptContinue();
	}
	else if (hasPlayer2Won())
	{
		cout << "Player 2 has won!" << endl;
		promptContinue();
	}
	else if (isBoardFull())
	{
		cout << "The board is full! It's a tie!" << endl;
		promptContinue();
	}
}

void Game::clearBoard()
{
	for (int i = 0; i < 9; ++i)
		_board[i] = ' ';
}

void Game::promptContinue()
{
	cout << "Play again? Y/N: ";
	char c;
	cin >> c;

	if (c == 'Y' || c == 'y')
	{
		clearBoard();
		_flags[1] = true;
		_flags[2] = false;
		_flags[3] = false;
	}
	else
		_flags[0] = false;
}

bool Game::isSpaceEmpty(unsigned int row, unsigned int col) const
{
	return _board(row, col) == ' ';
}

void Game::checkRow(unsigned int row)
{
	if ((_board(row, 0) == 'X') && (_board(row, 1) == 'X') && (_board(row, 2) == 'X'))
		_flags[2] = true;
	else if ((_board(row, 0) == 'O') && (_board(row, 1) == 'O') && (_board(row, 2) == 'O'))
		_flags[3] = true;
}

void Game::checkColumn(unsigned int col)
{
	if ((_board(0, col) == 'X') && (_board(1, col) == 'X') && (_board(2, col) == 'X'))
		_flags[2] = true;
	else if ((_board(0, col) == 'O') && (_board(1, col) == 'O') && (_board(2, col) == 'O'))
		_flags[3] = true;
}

void Game::checkDownRightDiagonal()
{
	if ((_board(0, 0) == 'X') && (_board(1, 1) == 'X') && (_board(2, 2) == 'X'))
		_flags[2] = true;
	else if ((_board(0, 0) == 'O') && (_board(1, 1) == 'O') && (_board(2, 2) == 'O'))
		_flags[3] = true;
}

void Game::checkUpRightDiagonal()
{
	if ((_board(2, 0) == 'X') && (_board(1, 1) == 'X') && (_board(0, 2) == 'X'))
		_flags[2] = true;
	else if ((_board(2, 0) == 'O') && (_board(1, 1) == 'O') && (_board(0, 2) == 'O'))
		_flags[3] = true;
}

Game::Game() : _window(VideoMode(600, 600), "TicTacToe", sf::Style::Titlebar | sf::Style::Close)
{
	load_texture(_boardTexture, "resources\\board.png");
	load_texture(_xTexture, "resources\\x.png");
	load_texture(_oTexture, "resources\\o.png");

	_boardSprite.setTexture(_boardTexture);
	_boardSprite.setScale(2.0f, 2.0f);

	for (int row_i = 0; row_i < 3; ++row_i)
	{
		for (int col_i = 0; col_i < 3; ++col_i)
		{
			_xSprites(row_i, col_i).setTexture(_xTexture);
			_xSprites(row_i, col_i).setScale(4.0f, 4.0f);
			_xSprites(row_i, col_i).setPosition(200.0f * col_i, 200.0f * row_i);
			_oSprites(row_i, col_i).setTexture(_oTexture);
			_oSprites(row_i, col_i).setScale(4.0f, 4.0f);
			_oSprites(row_i, col_i).setPosition(200.0f * col_i, 200.0f * row_i);
		}
	}

	for (int i = 0; i < 9; ++i)
		_board[i] = ' ';

	_flags[0] = true;
	_flags[1] = true;
}

bool Game::isGameRunning() const
{
	return _flags[0];
}

bool Game::isPlayer1Turn() const
{
	return _flags[1];
}

bool Game::hasPlayer1Won() const
{
	return _flags[2];
}

bool Game::hasPlayer2Won() const
{
	return _flags[3];
}

bool Game::isBoardFull() const
{
	for (int i = 0; i < 9; ++i)
	{
		if (_board[i] == ' ')
			return false;
	}

	return true;
}

bool Game::shouldProgress() const
{
	return _flags[4];
}

bool Game::mouseInput() const
{
	return _flags[5];
}

void Game::run()
{
	while (isGameRunning())
	{
		processEvents();
		update();
		render();
	}
}