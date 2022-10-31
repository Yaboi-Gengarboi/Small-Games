// JLibrary
// Statistics.ixx
// Created on 2022-08-20 by Justyn Durnford
// Last modified on 2022-08-22 by Justyn Durnford
// 

module;

#include "Arithmetic.hpp"

#include <algorithm>
using std::max;
using std::min;
using std::sort;

#include <array>
using std::array;

#include <cstddef>
using std::size_t;

#include <vector>
using std::vector;

export module Statistics;

import Array;
import FixedArray;

export namespace jlib
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	template <arithmetic T, size_t N>
	float average(const array<T, N>& arr)
	{
		float avg = 0.0f;

		for (size_t i = 0; i < N; ++i)
			avg += float(arr[i]) / float(N);

		return avg;
	}

	// 
	template <arithmetic T>
	float average(const vector<T>& vec)
	{
		float avg = 0.0f;
		constexpr size_t len = vec.size();

		for (size_t i = 0; i < len; ++i)
			avg += float(vec[i]) / float(len);

		return avg;
	}

	// 
	template <arithmetic T, size_t N>
	float average(const FixedArray<T, N>& arr)
	{
		float avg = 0.0f;

		for (size_t i = 0; i < N; ++i)
			avg += float(arr[i]) / float(N);

		return avg;
	}

	// 
	template <arithmetic T>
	float average(const Array<T>& arr)
	{
		float avg = 0.0f;
		constexpr size_t len = arr.size();

		for (size_t i = 0; i < len; ++i)
			avg += float(arr[i]) / float(len);

		return avg;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	template <arithmetic T, size_t N>
	float maximum(const array<T, N>& arr)
	{
		if (N == 0)
			return 0.0f;

		float maxim = float(arr[0]);

		for (size_t i = 1; i < N; ++i)
			maxim = max(maxim, float(arr[i]));

		return maxim;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	template <arithmetic T, size_t N>
	float minimum(const array<T, N>& arr)
	{
		if (N == 0)
			return 0.0f;

		float minim = float(arr[0]);

		for (size_t i = 1; i < N; ++i)
			minim = min(minim, float(arr[i]));

		return minim;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	template <arithmetic T, size_t N>
	float median(array<T, N> arr)
	{
		sort(arr.begin(), arr.end());

		if (N == 0)
			return 0.0f;
		else if (N % 2 == 0)
			return (float(arr[N / 2] - 1) + float(arr[N / 2])) / 2.0f;
		else
			return float(arr[N / 2]);
	}
}