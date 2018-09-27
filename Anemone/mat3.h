#pragma once

#include "Anemone.h"

#include <cstddef>

#include "vec3.h"
#include "mat4.h"

namespace Anemone
{
	class mat3
	{
	public:

		mat3();

		void set(AE_FLOAT _m0, AE_FLOAT _m1, AE_FLOAT _m2, AE_FLOAT _m3, AE_FLOAT _m4, AE_FLOAT _m5, AE_FLOAT _m6, AE_FLOAT _m7, AE_FLOAT _m8);

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

		void operator=(const mat4& mat4)
		{
			mat[0] = mat4[0];
			mat[1] = mat4[1];
			mat[2] = mat4[2];
			mat[3] = mat4[4];
			mat[4] = mat4[5];
			mat[5] = mat4[6];
			mat[6] = mat4[8];
			mat[7] = mat4[9];
			mat[8] = mat4[10];
		}

		mat3(const mat4& mat4)
		{
			mat[0] = mat4[0];
			mat[1] = mat4[1];
			mat[2] = mat4[2];
			mat[3] = mat4[4];
			mat[4] = mat4[5];
			mat[5] = mat4[6];
			mat[6] = mat4[8];
			mat[7] = mat4[9];
			mat[8] = mat4[10];
		}

	protected:
	private:

		AE_FLOAT mat[9];

	};

	namespace Math
	{
		extern mat3 multiply(const mat3& mat1, const mat3& mat2);

		extern vec3 multiply(const mat3& mat, const vec3& vec);

		extern mat3 transpose(const mat3& mat);

	};
};

#ifndef aem
#define aem Anemone::Math
#endif