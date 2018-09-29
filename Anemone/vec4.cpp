#include "vec4.h"
#include <math.h>

namespace Anemone
{
	namespace Math
	{
		AE_FLOAT dot(const vec4& vec1, const vec4& vec2)
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
		}

		vec4 normalize(const vec4& vec)
		{
			AE_FLOAT mag = 1.0f / vec.length();
			return vec4(vec.x * mag, vec.y * mag, vec.z * mag, vec.w * mag);
		}

		AE_BOOL equal(const vec4& vec1, const vec4& vec2, float epsilon)
		{
			return fabs(vec1.x - vec2.x) < epsilon && fabs(vec1.y - vec2.y) < epsilon && fabs(vec1.z - vec2.z) && fabs(vec1.w - vec2.w) < epsilon;
		}
	};

	vec4::vec4()
	{
		x = y = z = w;
	}

	vec4::vec4(AE_FLOAT _x, AE_FLOAT _y, AE_FLOAT _z, AE_FLOAT _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	vec4::vec4(const vec3& vec, AE_FLOAT _w)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = _w;
	}

	vec4::vec4(const vec2& vec1, const vec2& vec2)
	{
		x = vec1.x;
		y = vec1.y;
		z = vec2.x;
		w = vec2.y;
	}

	AE_FLOAT vec4::length() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	AE_FLOAT vec4::squareLength() const
	{
		return x * x + y * y + z * z + w * w;
	}

	AE_DOUBLE vec4::angle() const
	{
		return atan2(y, x);
	}

	AE_FLOAT vec4::distance(const vec4& vec) const
	{
		return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z) + (vec.w - w) * (vec.w - w));
	}

	vec4& vec4::operator=(const vec4& vec)
	{
		if (this == &vec)
			return *this;

		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
		return *this;
	}

	vec4& vec4::operator=(AE_FLOAT scalar)
	{
		x = scalar;
		y = scalar;
		z = scalar;
		w = scalar;
		return *this;
	}

	AE_BOOL vec4::operator==(const vec4& vec)
	{
		return (x == vec.x && y == vec.y && z == vec.z && w == vec.w);
	}

	AE_BOOL vec4::operator!=(const vec4& vec)
	{
		return !(*this == vec);
	}

	vec4& vec4::operator+=(const vec4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}

	vec4& vec4::operator+=(AE_FLOAT scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
		return *this;
	}

	vec4& vec4::operator-=(const vec4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}

	vec4& vec4::operator-=(AE_FLOAT scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
		return *this;
	}

	vec4& vec4::operator*=(const vec4& vec)
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		w *= vec.w;
		return *this;
	}

	vec4& vec4::operator*=(AE_FLOAT scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	vec4 vec4::operator+(vec4 vec)
	{
		return vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	vec4 vec4::operator+(AE_FLOAT scalar)
	{
		return vec4(x + scalar, y + scalar, z + scalar, w + scalar);
	}

	vec4 vec4::operator-(vec4 vec)
	{
		return vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}

	vec4 vec4::operator-(AE_FLOAT scalar)
	{
		return vec4(x - scalar, y - scalar, z - scalar, w - scalar);
	}

	vec4 vec4::operator*(vec4 vec)
	{
		return vec4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
	}

	vec4 vec4::operator*(AE_FLOAT scalar)
	{
		return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	vec4 vec4::operator/(vec4 vec)
	{
		return vec4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
	}

	vec4 vec4::operator/(AE_FLOAT scalar)
	{
		return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
	}
};