// Card Shuffling
// main.cpp
// Created on 2022-01-20 by Justyn Durnford
// Last modified on 2022-01-20 by Justyn Durnford
// Main file for the Card Shuffling project.

#include "Card.hpp"

#include "IntegerTypedefs.hpp"
using namespace jlib;

#include <iostream>
using std::cout;
using std::endl;

bool is_bit_set(u8 byte, u8 bit)
{
	return byte & (1 << bit);
}

void print_bool(bool value, bool end_line = false)
{
	if (value)
		cout << "true";
	else
		cout << "false";

	if (end_line)
		cout << endl;
}

void print_bit_flags(u8 byte)
{
	for (u8 i = 0; i < 8; ++i)
		print_bool(byte & (1 << (7 - i)), true);
}

int main()
{
	u8 a = 0b11000000;
	u8 b = 0b10010111;

	print_bool(is_bit_set(b, 6));

	return 0;
}