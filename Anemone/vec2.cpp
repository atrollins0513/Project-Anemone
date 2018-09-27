#include "vec2.h"
#include <math.h>

namespace Anemone
{
	namespace Math
	{
		AE_FLOAT dot(const vec2& vec1, const vec2& vec2)
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y);
		}

		vec2 normalize(const vec2& vec)
		{
			float mag = 1.0f / vec.length();
			return vec2(vec.x * mag, vec.y * mag);
		}

		AE_BOOL equal(const vec2& vec1, const vec2& vec2, float epsilon)
		{
			return fabs(vec1.x - vec2.x) < epsilon && fabs(vec1.y - vec2.y) < epsilon;
		}

		vec2 rotateZ(const vec2& vec, float angle)
		{
			float s = sinf(angle);
			float c = cosf(angle);

			return vec2(vec.x * c - vec.y * s, vec.x * s + vec.y * c);
		}
	};

	vec2::vec2()
	{
		x = y = 0.0f;
	}

	vec2::vec2(AE_FLOAT _x, AE_FLOAT _y)
	{
		x = _x;
		y = _y;
	}

	AE_FLOAT vec2::length() const
	{
		return sqrtf(x * x + y * y);
	}

	AE_FLOAT vec2::squareLength() const
	{
		return x * x + y * y;
	}

	AE_DOUBLE vec2::angle() const
	{
		return atan2(y, x);
	}

	AE_FLOAT vec2::distance(const vec2& vec) const
	{
		return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
	}

	vec2& vec2::operator=(const vec2& vec)
	{
		if (this == &vec)
			return *this;

		x = vec.x;
		y = vec.y;
		return *this;
	}

	vec2& vec2::operator=(AE_FLOAT scalar)
	{
		x = scalar;
		y = scalar;
		return *this;
	}

	AE_BOOL vec2::operator==(const vec2& vec)
	{
		return (x == vec.x && y == vec.y);
	}

	AE_BOOL vec2::operator!=(const vec2& vec)
	{
		return !(x == vec.x && y == vec.y);
	}

	vec2& vec2::operator+=(const vec2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	vec2& vec2::operator+=(AE_FLOAT scalar)
	{
		x += scalar;
		y += scalar;
		return *this;
	}

	vec2& vec2::operator-=(const vec2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	vec2& vec2::operator-=(AE_FLOAT scalar)
	{
		x -= scalar;
		y -= scalar;
		return *this;
	}

	vec2& vec2::operator*=(const vec2& vec)
	{
		x *= vec.x;
		y *= vec.y;
		return *this;
	}

	vec2& vec2::operator*=(AE_FLOAT scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	vec2 vec2::operator+(vec2 vec)
	{
		return vec2(x + vec.x, y + vec.y);
	}

	vec2 vec2::operator+(AE_FLOAT scalar)
	{
		return vec2(x + scalar, y + scalar);
	}

	vec2 vec2::operator-(vec2 vec)
	{
		return vec2(x - vec.x, y - vec.y);
	}

	vec2 vec2::operator-(AE_FLOAT scalar)
	{
		return vec2(x - scalar, y - scalar);
	}

	vec2 vec2::operator*(vec2 vec)
	{
		return vec2(x * vec.x, y * vec.y);
	}

	vec2 vec2::operator*(AE_FLOAT scalar)
	{
		return vec2(x * scalar, y * scalar);
	}

	vec2 vec2::operator/(vec2 vec)
	{
		return vec2(x / vec.x, y / vec.y);
	}

	vec2 vec2::operator/(AE_FLOAT scalar)
	{
		return vec2(x / scalar, y / scalar);
	}
};