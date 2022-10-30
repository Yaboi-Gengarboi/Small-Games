// RPGTest
// IDObject.hpp
// Created on 2022-09-28 by Justyn Durnford
// Last modified on 2022-10-04 by Justyn Durnford
// Header file for the IDObject class.

#pragma once

#include "IntegerTypedefs.hpp"
using jlib::u16;

#include <compare>
using std::strong_ordering;

#include <string>
using std::string;

// An IDObject has a name and an id attached to it
// so they can be compared with other IDObjects.
// 
class IDObject
{
	protected:

	u16 _id;
	string _name;

	public:

	// Default constructor.
	// Sets the ID to 0.
	IDObject();

	// u16 constructor.
	// Sets the ID to new_id.
	// Sets the name to new_name.
	IDObject(u16 new_id, const string& new_name);

	// Virtual destructor.
	virtual ~IDObject() = default;

	// Returns the id of the IDObject.
	u16 getID() const noexcept;

	// Returns a reference to the name of the IDObject.
	const string& getName() const noexcept;
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
std::strong_ordering operator <=> (const IDObject& A, const IDObject& B);