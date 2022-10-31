// JLibrary
// Vector2.ixx
// Created on 2022-01-08 by Justyn Durnford
// Last modified on 2022-03-25 by Justyn Durnford
// Module file for the Vector2 template class.

module;

#include "Angle.hpp"
#include "Arithmetic.hpp"
#include "IntegerTypedefs.hpp"

export module Vector2;

export namespace jlib
{
	// Utility template class for representing, manipulating
	// and computing with vectors in 2-dimensional space.
	template <arithmetic T> class Vector2
	{
		public:

		T x;
		T y;

		// Default constructor.
		// Sets the x component of the Vector2 to 0.
		// Sets the y component of the Vector2 to 0.
		Vector2()
		{
			x = 0;
			y = 0;
		}

		// Constructs the Vector2 from the given coordinates.
		// Sets the x component of the Vector2 to new_x.
		// Sets the y component of the Vector2 to new_y.
		Vector2(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Constructs the Vector2 from the given polar coordinates.
		// Sets the x component of the Vector2 to radius * cosine(angle).
		// Sets the y component of the Vector2 to radius * sine(angle).
		Vector2(T radius, Angle angle)
		{
			x = static_cast<T>(radius * cosine(angle));
			y = static_cast<T>(radius * sine(angle));
		}

		// Constructs the Vector2 as the displacement vector of the two points.
		// Sets the x component of the Vector2 to B.x - A.x.
		// Sets the y component of the Vector2 to B.y - A.y.
		Vector2(const Vector2<T>& A, const Vector2<T>& B)
		{
			x = B.x - A.x;
			y = B.y - A.y;
		}

		// Constructs the Vector2 from the components of the given std::array.
		// Sets the x component of the Vector2 to arr[0].
		// Sets the y component of the Vector2 to arr[1].
		Vector2(const std::array<T, 2> arr)
		{
			x = arr[0];
			y = arr[1];
		}

		// Default copy constructor.
		Vector2(const Vector2& other) = default;

		// Default move constructor.
		Vector2(Vector2&& other) = default;

		// Constructs the Vector2 from another type of Vector2.
		// This constructor doesn't replace the copy constructor,
		// it's called only when U != T.
		template <arithmetic U>
		explicit Vector2(const Vector2<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
		}

		// Assigns the Vector2 from the components of the given std::array.
		// Sets the x component of the Vector2 to arr[0].
		// Sets the y component of the Vector2 to arr[1].
		Vector2& operator = (const std::array<T, 2> arr)
		{
			x = arr[0];
			y = arr[1];

			return *this;
		}

		// Default copy assignment operator.
		Vector2& operator = (const Vector2& other) = default;

		// Default move assignment operator.
		Vector2& operator = (Vector2&& other) = default;

		// Destructor.
		~Vector2() = default;

		// Sets all the values of the Vector2 at once.
		// Sets the x component of the Vector2 to new_x.
		// Sets the y component of the Vector2 to new_y.
		void set(T new_x, T new_y)
		{
			x = new_x;
			y = new_y;
		}

		// Copies the components of a different type of Vector2.
		template <arithmetic U>
		void copyFrom(const Vector2<U>& other)
		{
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
		}

		// 
		void add(const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}

		// 
		void subtract(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
		}

		// 
		void multiply(const Vector2& other)
		{
			x *= other.x;
			y *= other.y;
		}

		// 
		template <arithmetic U>
		void multiply(U scalar)
		{
			x *= scalar;
			y *= scalar;
		}

		// 
		void divide(const Vector2& other)
		{
			x /= other.x;
			y /= other.y;
		}

		// 
		template <arithmetic U>
		void divide(U scalar)
		{
			x /= scalar;
			y /= scalar;
		}

		// Returns the magnitude of the Vector2.
		constexpr float magnitude() const
		{
			return std::sqrtf(std::powf(static_cast<float>(x), 2.0f) + std::powf(static_cast<float>(y), 2.0f));
		}

		// Returns the unit vector of this Vector2.
		Vector2<float> unitVector() const
		{
			const float m = magnitude();
			return Vector2<float>(x / m, y / m);
		}

		// Returns a normal vector of this Vector2.
		Vector2 normal()
		{
			return Vector2(-y, x);
		}

		// Returns a std::array with the components of the Vector2.
		std::array<T, 2> toArray() const
		{
			std::array<T, 2> arr = { x, y };
			return arr;
		}

		// Returns a std::string representation of the Vector2.
		std::string toString() const
		{
			return '<' + std::to_string(x) + ", " + std::to_string(y) + '>';
		}

		// Returns a std::wstring representation of the Vector2.
		std::wstring toWideString() const
		{
			return L'<' + std::to_wstring(x) + L", " + std::to_wstring(y) + L'>';
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Returns a Vector2 whose elements are the absolute values of 
	// each of the specified Vector2's elements.
	template <arithmetic T>
	inline Vector2<T> abs(const Vector2<T>& vec)
	{
		return Vector2<T>(std::abs(vec.x), std::abs(vec.y));
	}

	// Returns the distance between the 2 given Vector2s, treated as points.
	template <arithmetic T>
	constexpr float distance(const Vector2<T>& A, const Vector2<T>& B)
	{
		return std::sqrtf(std::powf(static_cast<float>(B.x - A.x), 2.0f) + std::powf(static_cast<float>(B.y - A.y), 2.0f));
	}

	// Returns the distance squared between the 2 given Vector2s, treated as points.
	template <arithmetic T>
	constexpr float distance_squared(const Vector2<T>& A, const Vector2<T>& B)
	{
		return std::powf(static_cast<float>(B.x - A.x), 2.0f) + std::powf(static_cast<float>(B.y - A.y), 2.0f);
	}

	// Returns the horizontal distance between the 2 given Vector2s.
	template <arithmetic T>
	constexpr float distance_x(const Vector2<T>& A, const Vector2<T>& B)
	{
		return B.x - A.x;
	}

	// Returns the vertical distance between the 2 given Vector2s.
	template <arithmetic T>
	constexpr float distance_y(const Vector2<T>& A, const Vector2<T>& B)
	{
		return B.y - A.y;
	}

	// Returns the dot product of the 2 given Vector2s.
	template <arithmetic T>
	constexpr float dot_product(const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.x * B.x + A.y * B.y;
	}

	// Returns the scalar projection of A onto B.
	template <arithmetic T>
	constexpr float comp_proj(const Vector2<T>& A, const Vector2<T>& B)
	{
		return dot_product(A, B) / B.magnitude();
	}

	// Returns the vector projection of A onto B.
	template <arithmetic T>
	Vector2<float> vector_proj(const Vector2<T>& A, const Vector2<T>& B)
	{
		float f = (dot_product(A, B) / dot_product(B, B));
		return Vector2<float>(B.x * f, B.y * f);
	}

	// Returns the angle between the 2 given Vector2s.
	template <arithmetic T>
	Angle angle_between(const Vector2<T>& A, const Vector2<T>& B)
	{
		return arccosine(dot_product(A, B) / (A.magnitude() * B.magnitude()));
	}

	// Checks if the 2 given Vector2s are orthogonal to eachother.
	template <arithmetic T>
	constexpr bool are_normal(const Vector2<T>& A, const Vector2<T>& B)
	{
		return dot_product(A, B) == 0.0f;
	}

	// Returns a Vector2 whose elements are the maximum of each of the 
	// pairs of elements in two specified Vector2s.
	template <arithmetic T>
	inline Vector2<T> max(const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(std::max(A.x, B.x), std::max(A.y, B.y));
	}

	// Returns a Vector2 whose elements are the minimum of each of the 
	// pairs of elements in two specified Vector2s.
	template <arithmetic T>
	inline Vector2<T> min(const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(std::min(A.x, B.x), std::min(A.y, B.y));
	}

	// 
	template <arithmetic T>
	void print(const Vector2<T>& vec)
	{
		std::cout << vec.toString();
	}

	// 
	template <arithmetic T>
	void println(const Vector2<T>& vec)
	{
		std::cout << vec.toString() << '\n';
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	typedef jlib::Vector2<bool>   Vector2b;
	typedef jlib::Vector2<i8>     Vector2c;
	typedef jlib::Vector2<u8>     Vector2uc;
	typedef jlib::Vector2<i16>    Vector2s;
	typedef jlib::Vector2<u16>    Vector2us;
	typedef jlib::Vector2<i32>    Vector2i;
	typedef jlib::Vector2<u32>    Vector2u;
	typedef jlib::Vector2<i64>    Vector2l;
	typedef jlib::Vector2<u64>    Vector2ul;
	typedef jlib::Vector2<size_t> Vector2uz;
	typedef jlib::Vector2<float>  Vector2f;
	typedef jlib::Vector2<double> Vector2d;

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Overload of binary operator ==
	template <arithmetic T>
	bool operator == (const Vector2<T>& A, const Vector2<T>& B)
	{
		return (A.x == B.x) && (A.y == B.y);
	}

	// Overload of binary operator !=
	template <arithmetic T>
	bool operator != (const Vector2<T>& A, const Vector2<T>& B)
	{
		return (A.x != B.x) || (A.y != B.y);
	}

	// Overload of binary operator <
	template <arithmetic T>
	bool operator < (const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.magnitude() < B.magnitude();
	}

	// Overload of binary operator <=
	template <arithmetic T>
	bool operator <= (const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.magnitude() <= B.magnitude();
	}

	// Overload of binary operator >
	template <arithmetic T>
	bool operator > (const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.magnitude() > B.magnitude();
	}

	// Overload of binary operator >=
	template <arithmetic T>
	bool operator >= (const Vector2<T>& A, const Vector2<T>& B)
	{
		return A.magnitude() >= B.magnitude();
	}

	// Overload of unary operator -
	template <arithmetic T>
	Vector2<T> operator - (const Vector2<T>& A)
	{
		return Vector2<T>(-A.x, -A.y);
	}

	// Overload of binary operator +
	template <arithmetic T>
	Vector2<T> operator + (const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(A.x + B.x, A.y + B.y);
	}

	// Overload of binary operator -
	template <arithmetic T>
	Vector2<T> operator - (const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(A.x - B.x, A.y - B.y);
	}

	// Overload of binary operator *
	template <arithmetic T>
	Vector2<T> operator * (const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(A.x * B.x, A.y * B.y);
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U>
	Vector2<T> operator * (const Vector2<T>& A, U scalar)
	{
		return Vector2<T>(A.x * scalar, A.y * scalar);
	}

	// Overload of binary operator *
	template <arithmetic T, arithmetic U>
	Vector2<T> operator * (U scalar, const Vector2<T>& A)
	{
		return Vector2<T>(A.x * scalar, A.y * scalar);
	}

	// Overload of binary operator /
	template <arithmetic T>
	Vector2<T> operator / (const Vector2<T>& A, const Vector2<T>& B)
	{
		return Vector2<T>(A.x / B.x, A.y / B.y);
	}

	// Overload of binary operator /
	template <arithmetic T, arithmetic U>
	Vector2<T> operator / (const Vector2<T>& A, U scalar)
	{
		return Vector2<T>(A.x / scalar, A.y / scalar);
	}

	// Overload of binary operator /
	template <arithmetic T, arithmetic U>
	Vector2<T> operator / (U scalar, const Vector2<T>& A)
	{
		return Vector2<T>(scalar / A.x, scalar / A.y);
	}

	// Overload of binary operator +=
	template <arithmetic T>
	Vector2<T>& operator += (Vector2<T>& A, const Vector2<T>& B)
	{
		A.add(B);
		return A;
	}

	// Overload of binary operator -=
	template <arithmetic T>
	Vector2<T>& operator -= (Vector2<T>& A, const Vector2<T>& B)
	{
		A.subtract(B);
		return A;
	}
	
	// Overload of binary operator *=
	template <arithmetic T>
	Vector2<T>& operator *= (Vector2<T>& A, const Vector2<T>& B)
	{
		A.multiply(B);
		return A;
	}

	// Overload of binary operator *=
	template <arithmetic T, arithmetic U>
	Vector2<T>& operator *= (Vector2<T>& A, U scalar)
	{
		A.multiply(scalar);
		return A;
	}

	// Overload of binary operator /=
	template <arithmetic T, arithmetic U>
	Vector2<T>& operator /= (Vector2<T>& A, U scalar)
	{
		A.divide(scalar);
		return A;
	}

	// Overload of binary operator /=
	template <arithmetic T>
	Vector2<T>& operator /= (Vector2<T>& A, const Vector2<T>& B)
	{
		A.divide(B);
		return A;
	}

	// Overload of std::ostream operator <<
	template <arithmetic T>
	std::ostream& operator << (std::ostream& os, const Vector2<T>& A)
	{
		os << A.toString();
		return os;
	}

	// Overload of std::wostream operator <<
	template <arithmetic T>
	std::wostream& operator << (std::wostream& wos, const Vector2<T>& A)
	{
		wos << A.toWideString();
		return wos;
	}
}