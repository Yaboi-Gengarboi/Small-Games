// Connect4
// Grid.cpp
// Created on 2022-03-23 by Justyn Durnford
// Last modified on 2022-08-15 by Justyn Durnford
// Implementation file for the Grid class.

#include "Grid.hpp"

constexpr char Grid::_getTokenCharacter(Token token) const
{
	switch (token)
	{
		case Token::RED:
			return 'X';
		break;

		case Token::YELLOW:
			return 'O';
		break;

		default:
			return ' ';
		break;
	}
}

Grid::Grid()
{
	fill(_data.data(), _data.dataEnd(), Token::NONE);
}

size_t Grid::rowCount() const noexcept
{
	return _data.rowCount();
}

size_t Grid::columnCount() const noexcept
{
	return _data.columnCount();
}

size_t Grid::size() const noexcept
{
	return _data.size();
}

Token Grid::getToken(size_t index) const
{
	return _data[index];
}

Token Grid::getToken(size_t row, size_t col) const
{
	return _data.at(row, col);
}

Token Grid::getToken(const Vector2i& pos) const
{
	return _data.at(pos.y, pos.x);
}

void Grid::setToken(Token token, size_t row, size_t col)
{
	_data.at(row, col) = token;
}

void Grid::setToken(Token token, const Vector2i& pos)
{
	_data.at(pos.y, pos.x) = token;
}

bool Grid::isColumnFull(size_t col) const
{
	if (col >= _data.columnCount())
		return true;

	return _data.at(0, col) != Token::NONE;
}

size_t Grid::currentRow(size_t col) const
{
	if(isColumnFull(col))
		return 6;

	for (size_t row_i = _data.rowCount() - 1; row_i > 0; --row_i)
	{
		if (_data.at(row_i, col) == Token::NONE)
			return row_i;
	}

	return 0;
}

bool Grid::dropToken(Token token, size_t col)
{
	size_t row = currentRow(col);

	if (row == 6)
		return false;

	setToken(token, row, col);

	return true;
}

void Grid::clear()
{
	fill(_data.data(), _data.dataEnd(), Token::NONE);
}

void Grid::print() const
{
	cout << "    ";

	for (size_t col_i = 0; col_i < _data.columnCount(); ++col_i)
		cout << col_i << ' ';

	cout << '\n';

	for (size_t row_i = 0; row_i < _data.rowCount(); ++row_i)
	{
		cout << row_i << " {";

		for (size_t col_i = 0; col_i < _data.columnCount() - 1; ++col_i)
			cout << ' ' << _getTokenCharacter(_data(row_i, col_i));

		cout << ' ' << _getTokenCharacter(_data(row_i, _data.rowCount())) << " }\n";
	}
}