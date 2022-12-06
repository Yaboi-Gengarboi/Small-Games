// JLibrary
// InputBuffer.hpp
// Created on 2022-12-03 by Justyn Durnford
// Last modified on 2022-12-03 by Justyn Durnford
// Header file for the InputBuffer class.

#pragma once

#include "IntegerTypedefs.hpp"

#include <bitset>
#include <compare>
#include <string>

namespace jlib
{
    class InputBuffer
    {
        public:

        enum Frame : u16
        {
            FRAME_0  = 0b1000000000000000,
            FRAME_1  = 0b0100000000000000,
            FRAME_2  = 0b0010000000000000,
            FRAME_3  = 0b0001000000000000,
            FRAME_4  = 0b0000100000000000,
            FRAME_5  = 0b0000010000000000,
            FRAME_6  = 0b0000001000000000,
            FRAME_7  = 0b0000000100000000,
            FRAME_8  = 0b0000000010000000,
            FRAME_9  = 0b0000000001000000,
            FRAME_10 = 0b0000000000100000,
            FRAME_11 = 0b0000000000010000,
            FRAME_12 = 0b0000000000001000,
            FRAME_13 = 0b0000000000000100,
            FRAME_14 = 0b0000000000000010,
            FRAME_15 = 0b0000000000000001
        };

        private:

        u16 _value;

        public:

        // Default constructor.
        // Sets the value of the InputBuffer to new_value.
        InputBuffer(u16 new_value = static_cast<u16>(0));

        // u16 assignment operator.
        InputBuffer& operator = (u16 new_value);

        // Returns the value of the InputBuffer.
        u16 getValue() const noexcept;

        // Sets the value of the InputBuffer.
        void setValue(u16 new_value) noexcept;

        // Updates the InputBuffer with the given state.
        void update(bool state) noexcept;

        // Returns true if the InputBuffer's current state is true.
        bool isActive() const noexcept;

        // Returns true if the InputBuffer's state was true
        // within the InputBuffer's bit count.
        bool wasActive() const noexcept;

        // Returns a std::string representation of the InputBuffer.
        std::string toString() const;
    };

    // 
    bool operator == (InputBuffer buff, u16 value);

    // 
    bool operator != (InputBuffer buff, u16 value);

    // 
    bool operator < (InputBuffer buff, u16 value);

    // 
    bool operator <= (InputBuffer buff, u16 value);

    // 
    bool operator > (InputBuffer buff, u16 value);

    // 
    bool operator >= (InputBuffer buff, u16 value);

    // 
    int compare(InputBuffer buff, u16 value);

    // 
    std::strong_ordering operator <=> (InputBuffer buff, u16 value);
}