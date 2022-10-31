// JLibrary
// LinearEquation.ixx
// Created on 2022-02-11 by Justyn Durnford
// Last modified on 2022-08-29 by Justyn Durnford
// Module file for the LinearEquation template class.

module;

#include "Arithmetic.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <string>

export module LinearEquation;

import Equation;
import FixedArray;

export namespace jlib
{
	// 
	template <arithmetic T, std::size_t> class LinearEquation : public Equation<T>
	class LinearEquation
	{
		public:

		FixedArray<T, N> coefficients;
		T constant;

		// Default constructor.
		LinearEquation()
		{
			std::fill(coefficients.data(), coefficients.dataEnd(), static_cast<T>(0));
			constant = static_cast<T>(0);
		}

		// 1-coefficient constructor.
	};
}