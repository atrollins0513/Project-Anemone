#pragma once

#include "Anemone.h"

#include "vec2.h"
#include "vec3.h"

namespace Anemone
{
	class vec4
	{
	public:

		AE_FLOAT x, y, z, w;

		vec4();

		vec4(AE_FLOAT _x, AE_FLOAT _y, AE_FLOAT _z, AE_FLOAT _w);

		vec4(const vec3& vec, AE_FLOAT _w);

		vec4(const vec2& vec1, const vec2& vec2);


		vec4& operator=(const vec4& vec);

		vec4& operator=(AE_FLOAT scalar);

		AE_BOOL operator==(const vec4& vec);

		AE_BOOL operator!=(const vec4& vec);

		vec4& operator+=(const vec4& vec);

		vec4& operator+=(AE_FLOAT scalar);

		vec4& operator-=(const vec4& vec);

		vec4& operator-=(AE_FLOAT scalar);

		vec4& operator*=(const vec4& vec);

		vec4& operator*=(AE_FLOAT scalar);


		vec4 operator+(vec4 vec);

		vec4 operator+(AE_FLOAT scalar);

		vec4 operator-(vec4 vec);

		vec4 operator-(AE_FLOAT scalar);

		vec4 operator*(vec4 vec);

		vec4 operator*(AE_FLOAT scalar);

		vec4 operator/(vec4 vec);

		vec4 operator/(AE_FLOAT scalar);


		AE_FLOAT length() const;

		AE_FLOAT squareLength() const;

		AE_DOUBLE angle() const;

		AE_FLOAT distance(const vec4& vec) const;


		vec4(const vec4& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}

	protected:
	private:
	};

	namespace Math
	{
		extern AE_FLOAT dot(const vec4& vec1, const vec4& vec2);

		extern vec4 normalize(const vec4& vec);

		extern AE_BOOL equal(const vec4& vec1, const vec4& vec2, float epsilon);

	};
};

#ifndef aem
#define aem Anemone::Math
#endif