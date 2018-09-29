#pragma once

#include "Anemone.h"

namespace Anemone
{
	class vec2
	{
	public:

		AE_FLOAT x, y;

		vec2();

		vec2(AE_FLOAT _x, AE_FLOAT _y);


		vec2& operator=(const vec2& vec);

		vec2& operator=(AE_FLOAT scalar);

		AE_BOOL operator==(const vec2& vec);

		AE_BOOL operator!=(const vec2& vec);

		vec2& operator+=(const vec2& vec);

		vec2& operator+=(AE_FLOAT scalar);

		vec2& operator-=(const vec2& vec);

		vec2& operator-=(AE_FLOAT scalar);

		vec2& operator*=(const vec2& vec);

		vec2& operator*=(AE_FLOAT scalar);


		vec2 operator+(vec2 vec);

		vec2 operator+(AE_FLOAT scalar);

		vec2 operator-(vec2 vec);

		vec2 operator-(AE_FLOAT scalar);

		vec2 operator*(vec2 vec);

		vec2 operator*(AE_FLOAT scalar);

		vec2 operator/(vec2 vec);

		vec2 operator/(AE_FLOAT scalar);


		AE_FLOAT length() const;

		AE_FLOAT squareLength() const;

		AE_DOUBLE angle() const;

		AE_FLOAT distance(const vec2& vec) const;


		vec2(const vec2& other)
		{
			x = other.x;
			y = other.y;
		}

	protected:
	private:
	};

	namespace Math
	{
		extern AE_FLOAT dot(const vec2& vec1, const vec2& vec2);

		extern vec2 normalize(const vec2& vec);

		extern AE_BOOL equal(const vec2& vec1, const vec2& vec2, float epsilon);

		extern vec2 rotateZ(const vec2& vec, float angle);

	};
};

#ifndef aem
#define aem Anemone::Math
#endif