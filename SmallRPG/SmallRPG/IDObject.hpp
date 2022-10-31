// SmallRPG
// IDObject.hpp
// Created on 19 July, 2022 by Justyn Durnford
// Last modified on 19 July, 2022 by Justyn Durnford
// Header file for the IDObject class.

#pragma once

#include "IntegerTypedefs.hpp"
using namespace jlib;

#include <compare>
using std::strong_ordering;

#include <string>
using std::string;

class IDObject
{
	public:

	u16 id;
	string name;

	// Default constructor.
	// Sets the ID to 0.
	IDObject();

	// u16 constructor.
	// Sets the ID to id.
	IDObject(u16 new_id, const string& new_name);

	// Virtual destructor.
	virtual ~IDObject() = default;

	// Moves the data from the given IDObject to this one.
	void moveFrom(IDObject& other) noexcept;
};

// Overload of binary operator ==
bool operator == (const IDObject& A, const IDObject& B);

// Overload of binary operator !=
bool operator != (const IDObject& A, const IDObject& B);

// Overload of binary operator <
bool operator < (const IDObject& A, const IDObject& B);

// Overload of binary operator <=
bool operator <= (const IDObject& A, const IDObject& B);

// Overload of binary operator >
bool operator > (const IDObject& A, const IDObject& B);

// Overload of binary operator >=
bool operator >= (const IDObject& A, const IDObject& B);

// Overload of binary operator <=>
strong_ordering operator <=> (const IDObject& A, const IDObject& B);