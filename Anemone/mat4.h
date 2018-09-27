#pragma once

#include "Anemone.h"

#include <cstddef>

#include "vec3.h"
#include "vec4.h"

namespace Anemone
{
	class mat4;

	namespace Math
	{
		extern mat4 identity();

		extern mat4 multiply(const mat4& mat1, const mat4& mat2);

		extern vec3 multiply(const mat4& mat, const vec3& vec);

		extern vec4 multiply(const mat4& mat, const vec4& vec);

		extern mat4 transpose(const mat4& mat);


		extern mat4 translate(AE_FLOAT x, AE_FLOAT y, AE_FLOAT z);

		extern mat4 scale(AE_FLOAT x, AE_FLOAT y, AE_FLOAT z);

		extern mat4 rotateX(AE_FLOAT radians);

		extern mat4 rotateY(AE_FLOAT radians);

		extern mat4 rotateZ(AE_FLOAT radians);


		extern mat4 Ortho(AE_FLOAT left, AE_FLOAT right, AE_FLOAT bottom, AE_FLOAT top, AE_FLOAT near, AE_FLOAT far);

		extern mat4 Frustum(AE_FLOAT left, AE_FLOAT right, AE_FLOAT bottom, AE_FLOAT top, AE_FLOAT near, AE_FLOAT far);

		extern mat4 LookAt(vec3 eye, vec3 target, vec3 up);

		extern mat4 Perspective(AE_FLOAT fovy, AE_FLOAT aspect, AE_FLOAT near, AE_FLOAT far);

	};

	class mat4
	{
	public:

		mat4();

		void set(AE_FLOAT _m0, AE_FLOAT _m1, AE_FLOAT _m2, AE_FLOAT _m3, AE_FLOAT _m4, AE_FLOAT _m5, AE_FLOAT _m6, AE_FLOAT _m7, AE_FLOAT _m8, AE_FLOAT _m9, AE_FLOAT _m10, AE_FLOAT _m11, AE_FLOAT _m12, AE_FLOAT _m13, AE_FLOAT _m14, AE_FLOAT _m15);

		AE_FLOAT* get() { return mat; }

		void zero();

		AE_FLOAT& operator[](std::size_t index)
		{
			return mat[index];
		}

		const AE_FLOAT& operator[](std::size_t index) const
		{
			return mat[index];
		}

		mat4 operator*(const mat4& other)
		{
			return Math::multiply(*this, other);
		}

	protected:
	private:

		AE_FLOAT mat[16];

	};
};

#ifndef aem
#define aem Anemone::Math
#endif