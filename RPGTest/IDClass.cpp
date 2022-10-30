// RPGTest
// IDObject.cpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-09-28 by Justyn Durnford
// Source file for the IDObject class.

#include "IDObject.hpp"

IDObject::IDObject()
{
	_id = 0;
}

IDObject::IDObject(u16 new_id, const string& new_name)
{
	_id = new_id;
	_name = new_name;
}

u16 IDObject::getID() const noexcept
{
	return _id;
}

const string& IDObject::getName() const noexcept
{
	return _name;
}

bool operator == (const IDObject& A, const IDObject& B)
{
	return A.getID() == B.getID();
}

bool operator != (const IDObject& A, const IDObject& B)
{
	return A.getID() != B.getID();
}

bool operator < (const IDObject& A, const IDObject& B)
{
	return A.getID() < B.getID();
}

bool operator <= (const IDObject& A, const IDObject& B)
{
	return A.getID() <= B.getID();
}

bool operator > (const IDObject& A, const IDObject& B)
{
	return A.getID() > B.getID();
}

bool operator >= (const IDObject& A, const IDObject& B)
{
	return A.getID() >= B.getID();
}

std::strong_ordering operator <=> (const IDObject& A, const IDObject& B)
{
	return A.getID() <=> B.getID();
}