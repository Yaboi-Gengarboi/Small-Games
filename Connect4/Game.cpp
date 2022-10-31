// Connect4
// Game.cpp
// Created on 2022-07-16 by Justyn Durnford
// Last modified on 2022-08-29 by Justyn Durnford
// Source file for the Game class.

#include "Game.hpp"

void Game::_processEvents()
{
	// Process events.
	while (_window.pollEvent(_event))
	{
		_mousePos = get_mouse_position(_window);

		switch (_event.type)
		{
			// Close window: exit.
			case Event::Closed:

				_window.close();
				exit(0);

			break;

			// Pressed Mouse button.
			case Event::MouseButtonPressed:

			

			break;

			default: break;
		}
	}
}

void Game::_update()
{
	for (size_t row_i = 0; row_i < _grid.rowCount(); ++row_i)
	{
		if (_checkRow(row_i))
		{
			_flags[0] = false;
			return;
		}
	}

	for (size_t col_i = 0; col_i < 7; ++col_i)
	{
		if (_checkColumn(col_i))
		{
			_flags[0] = false;
			return;
		}
	}
}

void Game::_render()
{
	#ifdef _DEBUG

	

	#endif // #ifdef _DEBUG

	_window.clear();
	_window.draw(_gridSprite);
	_window.display();
}

void Game::_promptContinue()
{
	
}

bool Game::_isSpaceEmpty(size_t row, size_t col) const
{
	return _grid.getToken(row, col) IS Token::NONE;
}

bool Game::_checkRow(size_t row)
{
	Token token1, token2;
	int counter = 0;

	for (size_t col_i = 1; col_i < 7; ++col_i)
	{
		token1 = _grid.getToken(row, col_i - 1);
		token2 = _grid.getToken(row, col_i);

		if (token1 IS token2)
		{
			++counter;

			if (counter IS 4 AND token1 IS Token::RED)
			{
				_flags[3] = true;
				return true;
			}
			else if (counter IS 4 AND token1 IS Token::YELLOW)
			{
				_flags[4] = true;
				return true;
			}
		}
		else
			counter = 0;
	}

	return false;
}

bool Game::_checkColumn(size_t col)
{
	Token token1, token2;
	int counter = 0;

	for (size_t row_i = 1; row_i < 6; ++row_i)
	{
		token1 = _grid.getToken(row_i - 1, col);
		token2 = _grid.getToken(row_i, col);

		if (token1 IS token2)
		{
			++counter;

			if (counter IS 4 AND token1 IS Token::RED)
			{
				_flags[3] = true;
				return true;
			}
			else if (counter IS 4 AND token1 IS Token::YELLOW)
			{
				_flags[4] = true;
				return true;
			}
		}
		else
			counter = 0;
	}

	return false;
}

bool Game::_checkUpRightDiagonal(size_t row, size_t col)
{
	Token token1, token2;
	int counter = 0, row_i = row, col_i = col;

	while (row_i > 0 AND col_i < _grid.columnCount() - 1)
	{
		token1 = _grid.getToken(row_i, col_i);
		token2 = _grid.getToken(static_cast<size_t>(row_i) - 1, static_cast<size_t>(col_i) + 1);

		if (token1 IS token2)
		{
			++counter;

			if (counter IS 4 AND token1 IS Token::RED)
			{
				_flags[3] = true;
				return true;
			}
			else if (counter IS 4 AND token1 IS Token::YELLOW)
			{
				_flags[4] = true;
				return true;
			}
		}
		else
			counter = 0;

		--row_i;
		++col_i;
	}

	return false;
}

bool Game::_checkUpLeftDiagonal(size_t row, size_t col)
{
	Token token1, token2;
	int counter = 0, row_i = row, col_i = col;

	while (row_i > 0 AND col_i > 0)
	{
		token1 = _grid.getToken(row_i, col_i);
		token2 = _grid.getToken(static_cast<size_t>(row_i) - 1, static_cast<size_t>(col_i) - 1);

		if (token1 IS token2)
		{
			++counter;

			if (counter IS 4 AND token1 IS Token::RED)
			{
				_flags[3] = true;
				return true;
			}
			else if (counter IS 4 AND token1 IS Token::YELLOW)
			{
				_flags[4] = true;
				return true;
			}
		}
		else
			counter = 0;

		--row_i;
		--col_i;
	}

	return false;
}

void Game::_checkDiagonals()
{
	if (_checkUpRightDiagonal(5, 3))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpRightDiagonal(5, 2))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpRightDiagonal(5, 1))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpRightDiagonal(5, 0))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpRightDiagonal(4, 0))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpRightDiagonal(3, 0))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpLeftDiagonal(5, 3))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpLeftDiagonal(5, 4))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpLeftDiagonal(5, 5))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpLeftDiagonal(5, 6))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpLeftDiagonal(4, 6))
	{
		_flags[0] = false;
		return;
	}
	else if (_checkUpLeftDiagonal(3, 6))
	{
		_flags[0] = false;
		return;
	}
}

Game::Game(int test_code) : _window(VideoMode(780, 490), "Connect 4", sf::Style::Titlebar | sf::Style::Close)
{
	_flags[0] = true;
	size_t row_i = 0, col_i = 0;

	switch (test_code)
	{
		case 1:

			for (col_i = 0; col_i < _grid.columnCount(); ++col_i)
				_grid.dropToken(Token::RED, col_i);

		break;

		case 2:

			row_i = 1, col_i = 1;

			while (row_i < _grid.rowCount() AND col_i < _grid.columnCount())
			{
				_grid.setToken(Token::YELLOW, row_i, col_i);
				_grid.print();
				++row_i;
				++col_i;
			}

		break;

		case 3:

			for (row_i = 0; row_i < _grid.rowCount() - 1; ++row_i)
				_grid.dropToken(Token::RED, 0);

		break;

		default:

		break;
	}

	if (!create_texture(_gridTexture, "resources\\grid.png"))
	{
		cerr << "ERROR: Could not load file: resources\\grid.png\n";
		exit(1);
	}

	if (!create_texture(_tokenTexture, "resources\\tokens.png"))
	{
		cerr << "ERROR: Could not load file: resources\\tokens.png\n";
		exit(1);
	}

	_gridSprite.setTexture(_gridTexture);
	
}

bool Game::isGameRunning() const noexcept
{
	return _flags[0];
}

bool Game::isPlayer1Turn() const noexcept
{
	return _flags[1];
}

bool Game::isPlayer2Turn() const noexcept
{
	return _flags[2];
}

bool Game::hasPlayer1Won() const noexcept
{
	return _flags[3];
}

bool Game::hasPlayer2Won() const noexcept
{
	return _flags[4];
}

bool Game::isBoardFull() const
{
	for (size_t col_i = 0; col_i < _grid.columnCount(); ++col_i)
	{
		if (_grid.getToken(0, col_i) IS Token::NONE)
			return false;
	}

	return true;
}

bool Game::shouldProgress() const noexcept
{
	return _flags[5];
}

bool Game::mouseInput() const noexcept
{
	return _flags[6];
}

void Game::run()
{
	while (isGameRunning())
	{
		_processEvents();
		_update();
		_render();
	}
}