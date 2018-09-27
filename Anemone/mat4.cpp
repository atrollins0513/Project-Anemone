#include "mat4.h"
#include <math.h>

namespace Anemone
{
	mat4::mat4()
	{
		zero();
		mat[0] = 1.0f;
		mat[5] = 1.0f;
		mat[10] = 1.0f;
		mat[15] = 1.0f;
	}

	void mat4::set(AE_FLOAT _m0, AE_FLOAT _m1, AE_FLOAT _m2, AE_FLOAT _m3, AE_FLOAT _m4, AE_FLOAT _m5, AE_FLOAT _m6, AE_FLOAT _m7, AE_FLOAT _m8, AE_FLOAT _m9, AE_FLOAT _m10, AE_FLOAT _m11, AE_FLOAT _m12, AE_FLOAT _m13, AE_FLOAT _m14, AE_FLOAT _m15)
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
		mat[9] = _m9;
		mat[10] = _m10;
		mat[11] = _m11;

		mat[12] = _m12;
		mat[13] = _m13;
		mat[14] = _m14;
		mat[15] = _m15;
	}


	void mat4::zero()
	{
		for (int i = 0; i < 16; i++)
		{
			mat[i] = 0.0f;
		}
	}

	namespace Math
	{
		mat4 identity()
		{
			mat4 mat;
			mat.zero();
			mat[0] = 1.0f;
			mat[5] = 1.0f;
			mat[10] = 1.0f;
			mat[15] = 1.0f;
			return mat;
		}

		mat4 multiply(const mat4& mat1, const mat4& mat2)
		{
			mat4 result;

			result[0] = mat1[0] * mat2[0] + mat1[4] * mat2[1] + mat1[8] * mat2[2] + mat1[12] * mat2[3];
			result[1] = mat1[1] * mat2[0] + mat1[5] * mat2[1] + mat1[9] * mat2[2] + mat1[13] * mat2[3];
			result[2] = mat1[2] * mat2[0] + mat1[6] * mat2[1] + mat1[10] * mat2[2] + mat1[14] * mat2[3];
			result[3] = mat1[3] * mat2[0] + mat1[7] * mat2[1] + mat1[11] * mat2[2] + mat1[15] * mat2[3];

			// Second Columat1n
			result[4] = mat1[0] * mat2[4] + mat1[4] * mat2[5] + mat1[8] * mat2[6] + mat1[12] * mat2[7];
			result[5] = mat1[1] * mat2[4] + mat1[5] * mat2[5] + mat1[9] * mat2[6] + mat1[13] * mat2[7];
			result[6] = mat1[2] * mat2[4] + mat1[6] * mat2[5] + mat1[10] * mat2[6] + mat1[14] * mat2[7];
			result[7] = mat1[3] * mat2[4] + mat1[7] * mat2[5] + mat1[11] * mat2[6] + mat1[15] * mat2[7];

			// Third Columat1n
			result[8] = mat1[0] * mat2[8] + mat1[4] * mat2[9] + mat1[8] * mat2[10] + mat1[12] * mat2[11];
			result[9] = mat1[1] * mat2[8] + mat1[5] * mat2[9] + mat1[9] * mat2[10] + mat1[13] * mat2[11];
			result[10] = mat1[2] * mat2[8] + mat1[6] * mat2[9] + mat1[10] * mat2[10] + mat1[14] * mat2[11];
			result[11] = mat1[3] * mat2[8] + mat1[7] * mat2[9] + mat1[11] * mat2[10] + mat1[15] * mat2[11];

			// Fourth Columat1n
			result[12] = mat1[0] * mat2[12] + mat1[4] * mat2[13] + mat1[8] * mat2[14] + mat1[12] * mat2[15];
			result[13] = mat1[1] * mat2[12] + mat1[5] * mat2[13] + mat1[9] * mat2[14] + mat1[13] * mat2[15];
			result[14] = mat1[2] * mat2[12] + mat1[6] * mat2[13] + mat1[10] * mat2[14] + mat1[14] * mat2[15];
			result[15] = mat1[3] * mat2[12] + mat1[7] * mat2[13] + mat1[11] * mat2[14] + mat1[15] * mat2[15];
		
			return result;
		}

		vec3 multiply(const mat4& mat, const vec3& vec)
		{
			vec3 result;

			result.x = mat[0] * vec.x + mat[1] * vec.y + mat[2] * vec.z + mat[3];
			result.y = mat[4] * vec.x + mat[5] * vec.y + mat[6] * vec.z + mat[7];
			result.z = mat[8] * vec.x + mat[9] * vec.y + mat[10] * vec.z + mat[11];

			return result;
		}

		vec4 multiply(const mat4& mat, const vec4& vec)
		{
			vec4 result;

			result.x = mat[0] * vec.x + mat[1] * vec.y + mat[2] * vec.z + mat[3] * vec.w;
			result.y = mat[4] * vec.x + mat[5] * vec.y + mat[6] * vec.z + mat[7] * vec.w;
			result.z = mat[8] * vec.x + mat[9] * vec.y + mat[10] * vec.z + mat[11] * vec.w;
			result.w = mat[12] * vec.x + mat[13] * vec.y + mat[14] * vec.z + mat[15] * vec.w;

			return result;
		}

		mat4 transpose(const mat4& mat)
		{
			mat4 tm;
			tm[0] = mat[0];
			tm[1] = mat[4];
			tm[2] = mat[8];
			tm[3] = mat[12];
			tm[4] = mat[1];
			tm[5] = mat[5];
			tm[6] = mat[9];
			tm[7] = mat[13];
			tm[8] = mat[2];
			tm[9] = mat[6];
			tm[10] = mat[10];
			tm[11] = mat[14];
			tm[12] = mat[3];
			tm[13] = mat[7];
			tm[14] = mat[11];
			tm[15] = mat[15];
			return tm;
		}

		mat4 translate(AE_FLOAT x, AE_FLOAT y, AE_FLOAT z)
		{
			mat4 trans;
			trans[12] = x;
			trans[13] = y;
			trans[14] = z;
			return trans;
		}

		mat4 scale(AE_FLOAT x, AE_FLOAT y, AE_FLOAT z)
		{
			mat4 scale;
			scale[0] = x;
			scale[5] = y;
			scale[10] = z;
			return scale;
		}

		mat4 rotateX(AE_FLOAT radians)
		{
			float c = cos(radians);
			float s = sin(radians);

			mat4 rotX;
			rotX[5] = c;
			rotX[6] = -s;
			rotX[9] = s;
			rotX[10] = c;
			return rotX;
		}

		mat4 rotateY(AE_FLOAT radians)
		{
			float c = cos(radians);
			float s = sin(radians);

			mat4 rotY;
			rotY[0] = c;
			rotY[2] = s;
			rotY[8] = -s;
			rotY[10] = c;

			return rotY;
		}

		mat4 rotateZ(AE_FLOAT radians)
		{
			float c = cosf(radians);
			float s = sinf(radians);

			mat4 rotZ;
			rotZ[0] = c;
			rotZ[1] = -s;
			rotZ[4] = s;
			rotZ[5] = c;

			return rotZ;
		}

		mat4 Ortho(AE_FLOAT left, AE_FLOAT right, AE_FLOAT bottom, AE_FLOAT top, AE_FLOAT near, AE_FLOAT far)
		{
			float rl = right - left;
			float tb = top - bottom;
			float fn = far - near;

			mat4 ortho;
			ortho.set(
				2 / rl, 0.0f, 0.0f, -(left + right) / rl,
				0.0f, 2 / tb, 0.0f, -(top + bottom) / tb,
				0.0f, 0.0f, -2 / fn, -(far + near) / fn,
				0.0f, 0.0f, 0.0f, 1.0f
			);
			return ortho;
		}

		mat4 Frustum(AE_FLOAT left, AE_FLOAT right, AE_FLOAT bottom, AE_FLOAT top, AE_FLOAT near, AE_FLOAT far)
		{
			float rl = right - left;
			float tb = top - bottom;
			float fn = far - near;

			mat4 frustum;
			frustum.set(
				(2.0f * near) / rl, 0.0f, (left + right) / rl, 0.0f,
				0.0f, (2.0f * near) / tb, (top + bottom) / tb, 0.0f,
				0.0f, 0.0f, (-(far + near)) / fn, (-2.0f * far * near) / fn,
				0.0f, 0.0f, -1.0f, 0.0f
			);
			return frustum;
		}

		mat4 LookAt(vec3 eye, vec3 target, vec3 up)
		{
			vec3 zaxis = normalize(eye - target);
			vec3 xaxis = normalize(cross(up, zaxis));
			vec3 yaxis = cross(zaxis, xaxis);

			mat4 lookAt;
			lookAt.set(xaxis.x, yaxis.x, zaxis.x, 0,
				xaxis.y, yaxis.y, zaxis.y, 0,
				xaxis.z, yaxis.z, zaxis.z, 0,
				-dot(xaxis, eye), -dot(yaxis, eye), -dot(zaxis, eye), 1
			);
			return lookAt;
		}

		mat4 Perspective(AE_FLOAT fovy, AE_FLOAT aspect, AE_FLOAT near, AE_FLOAT far)
		{
			float f = 1.0f / tanf(fovy / 2.0f);

			mat4 perspective;
			perspective.set((f / aspect), 0, 0, 0,
				0, f, 0, 0,
				0, 0, ((far + near) / (near - far)), ((2 * far * near) / (near - far)),
				0, 0, -1, 0
			);
			return perspective;
		}
	};
};