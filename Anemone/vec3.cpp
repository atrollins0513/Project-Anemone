#include "vec3.h"
#include <math.h>

namespace Anemone
{
	namespace Math
	{
		AE_FLOAT dot(const vec3& vec1, const vec3& vec2)
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
		}

		vec3 cross(const vec3& vec1, const vec3& vec2)
		{
			return vec3(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
		}

		vec3 normalize(const vec3& vec)
		{
			AE_FLOAT mag = 1.0f / vec.length();
			return vec3(vec.x * mag, vec.y * mag, vec.z * mag);
		}

		AE_BOOL equal(const vec3& vec1, const vec3& vec2, float epsilon)
		{
			return fabs(vec1.x - vec2.x) < epsilon && fabs(vec1.y - vec2.y) < epsilon && fabs(vec1.z - vec2.z) < epsilon;
		}

		vec3 rotateX(const vec3& vec, float angle)
		{
			AE_FLOAT s = sinf(angle);
			AE_FLOAT c = cosf(angle);

			return vec3(vec.x, c * vec.y - s * vec.z, c * vec.z + s * vec.y);
		}

		vec3 rotateY(const vec3& vec, float angle)
		{
			AE_FLOAT s = sinf(angle);
			AE_FLOAT c = cosf(angle);

			return vec3(c * vec.x + s * vec.z, vec.y, c * vec.z - s * vec.x);
		}

		vec3 rotateZ(const vec3& vec, float angle)
		{
			AE_FLOAT s = sinf(angle);
			AE_FLOAT c = cosf(angle);

			return vec3(c * vec.x - s * vec.y, c * vec.y + s * vec.x, vec.z);
		}
	};

	vec3::vec3()
	{
		x = y = z = 0.0f;
	}

	vec3::vec3(AE_FLOAT _x, AE_FLOAT _y, AE_FLOAT _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	AE_FLOAT vec3::length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	AE_FLOAT vec3::squareLength() const
	{
		return x * x + y * y + z * z;
	}

	AE_DOUBLE vec3::angle() const
	{
		return atan2(y, x);
	}

	AE_FLOAT vec3::distance(const vec3& vec) const
	{
		return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
	}

	vec3& vec3::operator=(const vec3& vec)
	{
		if (this == &vec)
			return *this;

		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	vec3& vec3::operator=(AE_FLOAT scalar)
	{
		x = scalar;
		y = scalar;
		z = scalar;
		return *this;
	}

	AE_BOOL vec3::operator==(const vec3& vec)
	{
		return (x == vec.x && y == vec.y && z == vec.z);
	}

	AE_BOOL vec3::operator!=(const vec3& vec)
	{
		return !(x == vec.x && y == vec.y && z == vec.z);
	}

	vec3& vec3::operator+=(const vec3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	vec3& vec3::operator+=(AE_FLOAT scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}

	vec3& vec3::operator-=(const vec3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	vec3& vec3::operator-=(AE_FLOAT scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}

	vec3& vec3::operator*=(const vec3& vec)
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}

	vec3& vec3::operator*=(AE_FLOAT scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	vec3 vec3::operator+(vec3 vec)
	{
		return vec3(x + vec.x, y + vec.y, z + vec.z);
	}

	vec3 vec3::operator+(AE_FLOAT scalar)
	{
		return vec3(x + scalar, y + scalar, z + scalar);
	}

	vec3 vec3::operator-(vec3 vec)
	{
		return vec3(x - vec.x, y - vec.y, z - vec.z);
	}

	vec3 vec3::operator-(AE_FLOAT scalar)
	{
		return vec3(x - scalar, y - scalar, z - scalar);
	}

	vec3 vec3::operator*(vec3 vec)
	{
		return vec3(x * vec.x, y * vec.y, z * vec.z);
	}

	vec3 vec3::operator*(AE_FLOAT scalar)
	{
		return vec3(x * scalar, y * scalar, z * scalar);
	}

	vec3 vec3::operator/(vec3 vec)
	{
		return vec3(x / vec.x, y / vec.y, z / vec.z);
	}

	vec3 vec3::operator/(AE_FLOAT scalar)
	{
		return vec3(x / scalar, y / scalar, z / scalar);
	}
};