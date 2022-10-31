// JLibrary
// Print.ixx
// Created on 24 July, 2022 by Justyn Durnford
// Last modified on 24 July, 2022 by Justyn Durnford
// 

module;

#include <iostream>

export module Print;

export namespace jlib
{
	template <typename T>
	void print(const T& var)
	{
		std::cout << var;
	}

	template <typename T>
	void print_wide(const T& var)
	{
		std::wcout << var;
	}

	template <typename T>
	void print_err(const T& var)
	{
		std::cerr << var;
	}

	template <typename T>
	void print_wide_err(const T& var)
	{
		std::wcerr << var;
	}

	template <typename T>
	void print_line(const T& var)
	{
		std::cout << var << '\n';
	}

	template <typename T>
	void print_wide_line(const T& var)
	{
		std::wcout << var << L'\n';
	}

	template <typename T>
	void print_err_line(const T& var)
	{
		std::cerr << var << L'\n';
	}

	template <typename T>
	void print_wide_err_line(const T& var)
	{
		std::wcerr << var << L'\n';
	}
}