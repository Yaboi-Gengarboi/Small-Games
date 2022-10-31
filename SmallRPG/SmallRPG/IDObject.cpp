// SmallRPG
// IDObject.cpp
// Created on 19 July, 2022 by Justyn Durnford
// Last modified on 19 July, 2022 by Justyn Durnford
// Source file for the IDObject class.

#include "IDObject.hpp"

#include <utility>
using std::move;

IDObject::IDObject()
{
	id = 0;
}

IDObject::IDObject(u16 new_id, const string& new_name)
{
	id = new_id;
	name = new_name;
}

void IDObject::moveFrom(IDObject& other) noexcept
{
	id = other.id;
	name = move(other.name);
}

bool operator == (const IDObject& A, const IDObject& B)
{
	return A.id == B.id;
}

bool operator != (const IDObject& A, const IDObject& B)
{
	return A.id != B.id;
}

bool operator < (const IDObject& A, const IDObject& B)
{
	return A.id < B.id;
}

bool operator <= (const IDObject& A, const IDObject& B)
{
	return A.id <= B.id;
}

bool operator > (const IDObject& A, const IDObject& B)
{
	return A.id > B.id;
}

bool operator >= (const IDObject& A, const IDObject& B)
{
	return A.id >= B.id;
}

strong_ordering operator <=> (const IDObject& A, const IDObject& B)
{
	return A.id <=> B.id;
}