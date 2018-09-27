#include "mat3.h"

namespace Anemone
{
	mat3::mat3()
	{
		zero();
		mat[0] = 1.0f;
		mat[4] = 1.0f;
		mat[8] = 1.0f;
	}

	void mat3::set(AE_FLOAT _m0, AE_FLOAT _m1, AE_FLOAT _m2, AE_FLOAT _m3, AE_FLOAT _m4, AE_FLOAT _m5, AE_FLOAT _m6, AE_FLOAT _m7, AE_FLOAT _m8)
	{
		mat[0] = _m0;
		mat[1] = _m1;
		mat[2] = _m2;
		mat[3] = _m3;
		mat[4] = _m4;
		mat[5] = _m5;
		mat[6] = _m6;
		mat[7] = _m7;
		mat[8] = _m8;
	}

	void mat3::zero()
	{
		for (int i = 0; i < 9; i++)
		{
			mat[i] = 0.0f;
		}
	}

	namespace Math
	{
		mat3 multiply(const mat3& mat1, const mat3& mat2)
		{
			mat3 result;

			result[0] = mat1[0] * mat2[0] + mat1[1] * mat2[3] + mat1[2] * mat2[6];
			result[1] = mat1[0] * mat2[1] + mat1[1] * mat2[4] + mat1[2] * mat2[7];
			result[2] = mat1[0] * mat2[2] + mat1[1] * mat2[5] + mat1[2] * mat2[8];

			result[3] = mat1[3] * mat2[0] + mat1[4] * mat2[3] + mat1[5] * mat2[6];
			result[4] = mat1[3] * mat2[1] + mat1[4] * mat2[4] + mat1[5] * mat2[7];
			result[5] = mat1[3] * mat2[2] + mat1[4] * mat2[5] + mat1[5] * mat2[8];

			result[6] = mat1[6] * mat2[0] + mat1[7] * mat2[3] + mat1[8] * mat2[6];
			result[7] = mat1[6] * mat2[1] + mat1[7] * mat2[4] + mat1[8] * mat2[7];
			result[8] = mat1[6] * mat2[2] + mat1[7] * mat2[5] + mat1[8] * mat2[8];

			return result;
		}

		vec3 multiply(const mat3& mat, const vec3& vec)
		{
			vec3 result;

			result.x = mat[0] * vec.x + mat[1] * vec.y + mat[2] * vec.z;
			result.y = mat[3] * vec.x + mat[4] * vec.y + mat[5] * vec.z;
			result.z = mat[6] * vec.x + mat[7] * vec.y + mat[8] * vec.z;

			return result;
		}

		mat3 transpose(const mat3& mat)
		{
			mat3 tm;
			tm[0] = mat[0];
			tm[1] = mat[3];
			tm[2] = mat[6];
			tm[3] = mat[1];
			tm[4] = mat[4];
			tm[5] = mat[7];
			tm[6] = mat[2];
			tm[7] = mat[5];
			tm[8] = mat[8];
			return tm;
		}
	};
};