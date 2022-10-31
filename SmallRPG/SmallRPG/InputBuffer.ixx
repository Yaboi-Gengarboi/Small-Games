// JLibrary
// InputBuffer.ixx
// Created on 2022-08-12 by Justyn Durnford
// Last modified on 2022-08-12 by Justyn Durnford
// Module file for the InputBuffer template class.

module;

#include <bitset>
#include <compare>
#include <concepts>
#include <string>

export module InputBuffer;

export namespace jlib
{
    // 
    template <std::unsigned_integral T> class InputBuffer
    {
        public:

        using value_type = T;

        private:

        value_type _value;

        public:

        // Default constructor.
        // Sets the value of the InputBuffer to new_value.
        InputBuffer(value_type new_value = static_cast<value_type>(0))
        {
            _value = new_value;
        }

        // Returns the value of the InputBuffer.
        constexpr value_type getValue() const noexcept
        {
            return _value;
        }

        // Sets the value of the InputBuffer.
        constexpr void setValue(value_type new_value) noexcept
        {
            _value = new_value;
        }

        // Updates the InputBuffer with the given state.
        constexpr void update(bool state) noexcept
        {
            _value >>= 1;
            _value |= state << (sizeof(value_type) * 8 - 1);
        }

        // Returns true if the InputBuffer's current state is true.
        constexpr bool isActive()
        {
            return _value >> sizeof(value_type) * 8 - 1;
        }

        // Returns true if the InputBuffer's state was true
        // within the InputBuffer's bit count.
        constexpr bool wasActive() const noexcept
        {
            return _value > static_cast<value_type>(0);
        }

        // Returns a std::string representation of the InputBuffer.
        std::string toString() const
        {
            return std::bitset<sizeof(value_type) * 8>(_value).to_string();
        }
    };

    // 
    template <std::unsigned_integral T>
    constexpr bool operator == (InputBuffer<T> buff, T value)
    {
        return buff.getValue() == value;
    }

    // 
    template <std::unsigned_integral T>
    constexpr bool operator != (InputBuffer<T> buff, T value)
    {
        return buff.getValue() != value;
    }

    // 
    template <std::unsigned_integral T>
    constexpr bool operator < (InputBuffer<T> buff, T value)
    {
        return buff.getValue() < value;
    }

    // 
    template <std::unsigned_integral T>
    constexpr bool operator <= (InputBuffer<T> buff, T value)
    {
        return buff.getValue() <= value;
    }

    // 
    template <std::unsigned_integral T>
    constexpr bool operator > (InputBuffer<T> buff, T value)
    {
        return buff.getValue() > value;
    }

    // 
    template <std::unsigned_integral T>
    constexpr bool operator >= (InputBuffer<T> buff, T value)
    {
        return buff.getValue() >= value;
    }

    // 
    template <std::unsigned_integral T>
    constexpr int compare(InputBuffer<T> buff, T value)
    {
        if (buff.getValue() < value)
            return -1;
        if (buff.getValue() > value)
            return 1;
        return 0;
    }

    // 
    template <std::unsigned_integral T>
    std::strong_ordering operator <=> (InputBuffer<T> buff, T value)
    {
        return buff.getValue() <=> value;
    }
}