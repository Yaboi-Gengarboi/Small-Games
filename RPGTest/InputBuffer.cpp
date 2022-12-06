// JLibrary
// InputBuffer.cpp
// Created on 2022-12-03 by Justyn Durnford
// Last modified on 2022-12-03 by Justyn Durnford
// Source file for the InputBuffer class.

#include "InputBuffer.hpp"

#include <bitset>
using std::bitset;

#include <compare>
using std::strong_ordering;

#include <string>
using std::string;

namespace jlib
{
    InputBuffer::InputBuffer(u16 new_value)
    {
        _value = new_value;
    }

    InputBuffer& InputBuffer::operator = (u16 new_value)
    {
        _value = new_value;
        return *this;
    }

    u16 InputBuffer::getValue() const noexcept
    {
        return _value;
    }

    void InputBuffer::setValue(u16 new_value) noexcept
    {
        _value = new_value;
    }

    void InputBuffer::update(bool state) noexcept
    {
        _value >>= 1;
        _value |= state << 15;
    }

    bool InputBuffer::isActive() const noexcept
    {
        return _value >= FRAME_0;
    }

    bool InputBuffer::wasActive() const noexcept
    {
        return _value > static_cast<u16>(0);
    }

    string InputBuffer::toString() const
    {
        return bitset<16>(_value).to_string();
    }

    bool operator == (InputBuffer buff, u16 value)
    {
        return buff.getValue() == value;
    }

    bool operator != (InputBuffer buff, u16 value)
    {
        return buff.getValue() != value;
    }

    bool operator < (InputBuffer buff, u16 value)
    {
        return buff.getValue() < value;
    }

    bool operator <= (InputBuffer buff, u16 value)
    {
        return buff.getValue() <= value;
    }

    bool operator > (InputBuffer buff, u16 value)
    {
        return buff.getValue() > value;
    }

    bool operator >= (InputBuffer buff, u16 value)
    {
        return buff.getValue() >= value;
    }

    int compare(InputBuffer buff, u16 value)
    {
        if (buff.getValue() < value)
            return -1;
        if (buff.getValue() > value)
            return 1;
        return 0;
    }

    strong_ordering operator <=> (InputBuffer buff, u16 value)
    {
        return buff.getValue() <=> value;
    }
}