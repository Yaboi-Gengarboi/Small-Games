// JLibrary
// Grid.ixx
// Created on 2022-07-05 by Justyn Durnford
// Last modified on 2022-07-05 by Justyn Durnford
// Module file for the Grid class.

module;

#include <bitset>
#include <cstddef>
#include <stdexcept>

export module Grid;

export namespace jlib
{
	// 
	template <std::size_t R, std::size_t C> class Grid
	{
		std::bitset<R* C> _data;

		public:

		// Default constructor.
		Grid() = default;

		// boolean constructor.
		// Sets every bit of the Grid to the given boolean.
		Grid(bool value)
		{
			_data.set(value);
		}

		// Returns the number of rows in the Grid.
		constexpr std::size_t rowCount() const noexcept
		{
			return R;
		}

		// Returns the number of columns in the Grid.
		constexpr std::size_t colCount() const noexcept
		{
			return C;
		}

		// Returns the number of bits in the Grid.
		constexpr std::size_t size() const noexcept
		{
			return R * C;
		}

		// Returns the underlying std::bitset.
		constexpr std::bitset<R * C>& data() noexcept
		{
			return _data;
		}

		// Returns the underlying std::bitset.
		constexpr const std::bitset<R * C>& data() const noexcept
		{
			return _data;
		}

		// Returns the bit at the given index of the Grid.
		// Throws a std::out_of_range if given an invalid index.
		constexpr bool at(std::size_t n)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid grid index");

			return _data[n];
		}

		// Returns the bit at the given index of the Grid.
		// Throws a std::out_of_range if given an invalid index.
		constexpr const bool at(std::size_t n) const
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid grid index");

			return _data[n];
		}

		// Returns the bit at [row][col].
		// Throws a std::out_of_range if given an invalid index.
		constexpr bool at(std::size_t row, std::size_t col)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(row * C) + col];
		}

		// Returns the bit at [row][col].
		// Throws a std::out_of_range if given an invalid index.
		constexpr const bool at(std::size_t row, std::size_t col) const
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			return _data[(row * C) + col];
		}

		// Sets the bit at the given index to the given value.
		// Throws a std::out_of_range if given an invalid index.
		constexpr void set(std::size_t n, bool value)
		{
			if (n >= R * C)
				throw std::out_of_range("Invalid grid index");

			_data[n] = value;
		}

		// Sets the bit at [row][col] to the given value.
		// Throws a std::out_of_range if given an invalid index.
		constexpr void set(std::size_t row, std::size_t col, bool value)
		{
			if (row >= R)
				throw std::out_of_range("Invalid row index");
			if (col >= C)
				throw std::out_of_range("Invalid column index");

			_data[(row * C) + col] = value;
		}

		// Returns the bit at the given index of the Grid.
		// Does NOT perform bounds-checking.
		constexpr bool operator [] (std::size_t n) const
		{
			return _data[n];
		}

		// Returns the bit at [row][col].
		// Does NOT perform bounds-checking.
		constexpr bool operator () (std::size_t row, std::size_t col) const
		{
			return _data[(row * C) + col];
		}
	};
}