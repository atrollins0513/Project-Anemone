#pragma once

#include "Anemone.h"

namespace Anemone
{
	class vec3
	{
	public:

		AE_FLOAT x, y, z;

		vec3();

		vec3(AE_FLOAT _x, AE_FLOAT _y, AE_FLOAT _z);


		vec3& operator=(const vec3& vec);

		vec3& operator=(AE_FLOAT scalar);

		AE_BOOL operator==(const vec3& vec);

		AE_BOOL operator!=(const vec3& vec);

		vec3& operator+=(const vec3& vec);

		vec3& operator+=(AE_FLOAT scalar);

		vec3& operator-=(const vec3& vec);

		vec3& operator-=(AE_FLOAT scalar);

		vec3& operator*=(const vec3& vec);

		vec3& operator*=(AE_FLOAT scalar);


		vec3 operator+(vec3 vec);

		vec3 operator+(AE_FLOAT scalar);

		vec3 operator-(vec3 vec);

		vec3 operator-(AE_FLOAT scalar);

		vec3 operator*(vec3 vec);

		vec3 operator*(AE_FLOAT scalar);

		vec3 operator/(vec3 vec);

		vec3 operator/(AE_FLOAT scalar);


		AE_FLOAT length() const;

		AE_FLOAT squareLength() const;

		AE_DOUBLE angle() const;

		AE_FLOAT distance(const vec3& vec) const;


		vec3(const vec3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}

	protected:
	private:
	};

	namespace Math
	{
		extern AE_FLOAT dot(const vec3& vec1, const vec3& vec2);

		extern vec3 cross(const vec3& vec1, const vec3& vec2);

		extern vec3 normalize(const vec3& vec);

		extern AE_BOOL equal(const vec3& vec1, const vec3& vec2, float epsilon);


		extern vec3 rotateX(const vec3& vec, float angle);

		extern vec3 rotateY(const vec3& vec, float angle);

		extern vec3 rotateZ(const vec3& vec, float angle);

	};
};

#ifndef aem
#define aem Anemone::Math
#endif