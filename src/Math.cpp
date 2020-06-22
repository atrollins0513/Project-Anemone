#include "..\Anemone\Math.h"

namespace Anemone
{
	/* 2D Vector */

	float dot(const vec2& vec1, const vec2& vec2)
	{
		return (vec1.x * vec2.x + vec1.y * vec2.y);
	}

	vec2 normalize(const vec2& vec)
	{
		float mag = 1.0f / vec.length();
		return vec2(vec.x * mag, vec.y * mag);
	}

	bool equal(const vec2& vec1, const vec2& vec2, float epsilon)
	{
		return fabs((double)vec1.x - (double)vec2.x) < epsilon && fabs((double)vec1.y - (double)vec2.y) < epsilon;
	}

	vec2 rotateZ(const vec2& vec, float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);

		return vec2(vec.x * c - vec.y * s, vec.x * s + vec.y * c);
	}

	vec2 rotateZ(const vec2& vec, double s, double c)
	{
		return vec2(vec.x * c - vec.y * s, vec.x * s + vec.y * c);
	}

	void print(const vec2& vec)
	{
		std::cout << "x: " << vec.x << " y: " << vec.y << "\n";
	}

	vec2 perpcw(const vec2& vec)
	{
		return vec2(vec.y, -vec.x);
	}

	vec2 perpccw(const vec2& vec)
	{
		return vec2(-vec.y, vec.x);
	}

	/* 3D Vector */

	float dot(const vec3& vec1, const vec3& vec2)
	{
		return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
	}

	vec3 cross(const vec3& vec1, const vec3& vec2)
	{
		return vec3(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
	}

	vec3 normalize(const vec3& vec)
	{
		float mag = 1.0f / vec.length();
		return vec3(vec.x * mag, vec.y * mag, vec.z * mag);
	}

	bool equal(const vec3& vec1, const vec3& vec2, float epsilon)
	{
		return fabs((double)vec1.x - (double)vec2.x) < epsilon && fabs((double)vec1.y - (double)vec2.y) < epsilon && fabs((double)vec1.z - (double)vec2.z) < epsilon;
	}

	vec3 rotateX(const vec3& vec, float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);

		return vec3(vec.x, c * vec.y - s * vec.z, c * vec.z + s * vec.y);
	}

	vec3 rotateX(const vec3& vec, double s, double c)
	{
		return vec3(vec.x, c * vec.y - s * vec.z, c * vec.z + s * vec.y);
	}

	vec3 rotateY(const vec3& vec, float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);

		return vec3(c * vec.x + s * vec.z, vec.y, c * vec.z - s * vec.x);
	}

	vec3 rotateY(const vec3& vec, double s, double c)
	{
		return vec3(c * vec.x + s * vec.z, vec.y, c * vec.z - s * vec.x);
	}

	vec3 rotateZ(const vec3& vec, float angle)
	{
		float s = sinf(angle);
		float c = cosf(angle);

		return vec3(c * vec.x - s * vec.y, c * vec.y + s * vec.x, vec.z);
	}

	vec3 rotateZ(const vec3& vec, double s, double c)
	{
		return vec3(c * vec.x - s * vec.y, c * vec.y + s * vec.x, vec.z);
	}

	void print(const vec3& vec)
	{
		std::cout << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << "\n";
	}

	/* 4D Vector */

	float dot(const vec4& vec1, const vec4& vec2)
	{
		return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
	}

	vec4 normalize(const vec4& vec)
	{
		float mag = 1.0f / vec.length();
		return vec4(vec.x * mag, vec.y * mag, vec.z * mag, vec.w * mag);
	}

	bool equal(const vec4& vec1, const vec4& vec2, float epsilon)
	{
		return fabs((double)vec1.x - (double)vec2.x) < epsilon && fabs((double)vec1.y - (double)vec2.y) < epsilon && fabs((double)vec1.z - (double)vec2.z) && fabs((double)vec1.w - (double)vec2.w) < epsilon;
	}

	void print(const vec4& vec)
	{
		std::cout << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << " w: " << vec.w << "\n";
	}

	/* 3x3 Matrix */

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

	void print(const Anemone::mat3& mat)
	{
		std::cout << mat[0] << "\t\t" << mat[1] << "\t\t" << mat[2] << "\n";
		std::cout << mat[3] << "\t\t" << mat[4] << "\t\t" << mat[5] << "\n";
		std::cout << mat[6] << "\t\t" << mat[7] << "\t\t" << mat[8] << "\n";
	}

	/* 4x4 Matrix */

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

	mat4 translate(float x, float y, float z)
	{
		mat4 trans;
		trans[12] = x;
		trans[13] = y;
		trans[14] = z;
		return trans;
	}

	mat4 scale(float x, float y, float z)
	{
		mat4 scale;
		scale[0] = x;
		scale[5] = y;
		scale[10] = z;
		return scale;
	}

	mat4 rotateX(float radians)
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

	mat4 rotateY(float radians)
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

	mat4 rotateZ(float radians)
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

	mat4 Ortho(float left, float right, float bottom, float top, float near, float far)
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

	mat4 Frustum(float left, float right, float bottom, float top, float near, float far)
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

	mat4 Perspective(float fovy, float aspect, float near, float far)
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

	void print(const Anemone::mat4& mat)
	{
		std::cout << mat[0] << "\t\t" << mat[1] << "\t\t" << mat[2] << "\t\t" << mat[3] << "\n";
		std::cout << mat[4] << "\t\t" << mat[5] << "\t\t" << mat[6] << "\t\t" << mat[7] << "\n";
		std::cout << mat[8] << "\t\t" << mat[9] << "\t\t" << mat[10] << "\t\t" << mat[11] << "\n";
		std::cout << mat[12] << "\t\t" << mat[13] << "\t\t" << mat[14] << "\t\t" << mat[15] << "\n";
	}

	/* Quaternion */

	Quaternion multiply(const Quaternion& q1, const Quaternion& q2)
	{
		return Quaternion(
			q1.values.w*q2.values.w - q1.values.x*q2.values.x - q1.values.y*q2.values.y - q1.values.z*q2.values.z,
			q1.values.w*q2.values.x + q1.values.x*q2.values.w + q1.values.y*q2.values.z - q1.values.z*q2.values.y,
			q1.values.w*q2.values.y + q1.values.y*q2.values.w + q1.values.z*q2.values.x - q1.values.x*q2.values.z,
			q1.values.w*q2.values.z + q1.values.z*q2.values.w + q1.values.x*q2.values.y - q1.values.y*q2.values.x);
	}

	/* 2D Vector */

	vec2::vec2()
	{
		x = y = 0.0f;
	}

	vec2::vec2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float vec2::length() const
	{
		return sqrtf(x * x + y * y);
	}

	float vec2::squareLength() const
	{
		return x * x + y * y;
	}

	double vec2::angle() const
	{
		return atan2(y, x);
	}

	float vec2::distance(const vec2& vec) const
	{
		return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
	}

	void vec2::normalize()
	{
		float mag = 1.0f / length();
		x *= mag;
		y *= mag;
	}

	void vec2::inverse()
	{
		x *= -1.0f;
		y *= -1.0f;
	}

	vec2& vec2::operator=(const vec2& vec)
	{
		if (this == &vec)
			return *this;

		x = vec.x;
		y = vec.y;
		return *this;
	}

	vec2& vec2::operator=(float scalar)
	{
		x = scalar;
		y = scalar;
		return *this;
	}

	bool vec2::operator==(const vec2& vec)
	{
		return (x == vec.x && y == vec.y);
	}

	bool vec2::operator!=(const vec2& vec)
	{
		return !(x == vec.x && y == vec.y);
	}

	vec2& vec2::operator+=(const vec2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	vec2& vec2::operator+=(float scalar)
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

	vec2& vec2::operator-=(float scalar)
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

	vec2& vec2::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	vec2& vec2::operator/=(const vec2& vec)
	{
		x /= vec.x;
		y /= vec.y;
		return *this;
	}

	vec2& vec2::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	vec2 vec2::operator+(vec2 vec)
	{
		return vec2(x + vec.x, y + vec.y);
	}

	vec2 vec2::operator+(float scalar)
	{
		return vec2(x + scalar, y + scalar);
	}

	vec2 vec2::operator-(vec2 vec)
	{
		return vec2(x - vec.x, y - vec.y);
	}

	vec2 vec2::operator-(float scalar)
	{
		return vec2(x - scalar, y - scalar);
	}

	vec2 vec2::operator*(vec2 vec)
	{
		return vec2(x * vec.x, y * vec.y);
	}

	vec2 vec2::operator*(float scalar)
	{
		return vec2(x * scalar, y * scalar);
	}

	vec2 vec2::operator/(vec2 vec)
	{
		return vec2(x / vec.x, y / vec.y);
	}

	vec2 vec2::operator/(float scalar)
	{
		return vec2(x / scalar, y / scalar);
	}

	vec2::vec2(const vec3& other)
	{
		x = other.x;
		y = other.y;
	}

	vec2::vec2(const vec2& other)
	{
		x = other.x;
		y = other.y;
	}

	/* 3D Vector */

	vec3::vec3()
	{
		x = y = z = 0.0f;
	}

	vec3::vec3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float vec3::length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float vec3::squareLength() const
	{
		return x * x + y * y + z * z;
	}

	double vec3::angle() const
	{
		return atan2(y, x);
	}

	float vec3::distance(const vec3& vec) const
	{
		return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
	}

	void vec3::normalize()
	{
		float mag = 1.0f / length();
		x *= mag;
		y *= mag;
		z *= mag;
	}

	void vec3::inverse()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
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

	vec3& vec3::operator=(float scalar)
	{
		x = scalar;
		y = scalar;
		z = scalar;
		return *this;
	}

	bool vec3::operator==(const vec3& vec)
	{
		return (x == vec.x && y == vec.y && z == vec.z);
	}

	bool vec3::operator!=(const vec3& vec)
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

	vec3& vec3::operator+=(float scalar)
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

	vec3& vec3::operator-=(float scalar)
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

	vec3& vec3::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	vec3& vec3::operator/=(const vec3& vec)
	{
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}

	vec3& vec3::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	vec3 vec3::operator+(vec3 vec)
	{
		return vec3(x + vec.x, y + vec.y, z + vec.z);
	}

	vec3 vec3::operator+(float scalar)
	{
		return vec3(x + scalar, y + scalar, z + scalar);
	}

	vec3 vec3::operator-(vec3 vec)
	{
		return vec3(x - vec.x, y - vec.y, z - vec.z);
	}

	vec3 vec3::operator-(float scalar)
	{
		return vec3(x - scalar, y - scalar, z - scalar);
	}

	vec3 vec3::operator*(vec3 vec)
	{
		return vec3(x * vec.x, y * vec.y, z * vec.z);
	}

	vec3 vec3::operator*(float scalar)
	{
		return vec3(x * scalar, y * scalar, z * scalar);
	}

	vec3 vec3::operator/(vec3 vec)
	{
		return vec3(x / vec.x, y / vec.y, z / vec.z);
	}

	vec3 vec3::operator/(float scalar)
	{
		return vec3(x / scalar, y / scalar, z / scalar);
	}

	vec3::vec3(const vec2& other)
	{
		x = other.x;
		y = other.y;
		z = 0.0f;
	}

	vec3::vec3(const vec4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	vec3::vec3(const vec3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	/* 4D Vector */

	vec4::vec4()
	{
		x = y = z = w = 0.0f;
	}

	vec4::vec4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	vec4::vec4(const vec3& vec, float _w)
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

	float vec4::length() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	float vec4::squareLength() const
	{
		return x * x + y * y + z * z + w * w;
	}

	double vec4::angle() const
	{
		return atan2(y, x);
	}

	float vec4::distance(const vec4& vec) const
	{
		return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z) + (vec.w - w) * (vec.w - w));
	}

	void vec4::normalize()
	{
		float mag = 1.0f / length();
		x *= mag;
		y *= mag;
		z *= mag;
		w *= mag;
	}

	void vec4::inverse()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
		w *= -1.0f;
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

	vec4& vec4::operator=(float scalar)
	{
		x = scalar;
		y = scalar;
		z = scalar;
		w = scalar;
		return *this;
	}

	bool vec4::operator==(const vec4& vec)
	{
		return (x == vec.x && y == vec.y && z == vec.z && w == vec.w);
	}

	bool vec4::operator!=(const vec4& vec)
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

	vec4& vec4::operator+=(float scalar)
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

	vec4& vec4::operator-=(float scalar)
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

	vec4& vec4::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	vec4& vec4::operator/=(const vec4& vec)
	{
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		w /= vec.w;
		return *this;
	}

	vec4& vec4::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}

	vec4 vec4::operator+(vec4 vec)
	{
		return vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	vec4 vec4::operator+(float scalar)
	{
		return vec4(x + scalar, y + scalar, z + scalar, w + scalar);
	}

	vec4 vec4::operator-(vec4 vec)
	{
		return vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}

	vec4 vec4::operator-(float scalar)
	{
		return vec4(x - scalar, y - scalar, z - scalar, w - scalar);
	}

	vec4 vec4::operator*(vec4 vec)
	{
		return vec4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
	}

	vec4 vec4::operator*(float scalar)
	{
		return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	vec4 vec4::operator/(vec4 vec)
	{
		return vec4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
	}

	vec4 vec4::operator/(float scalar)
	{
		return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
	}

	vec4::vec4(const vec2& other)
	{
		x = other.x;
		y = other.y;
		z = 0.0f;
		w = 0.0f;
	}

	vec4::vec4(const vec3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = 0.0f;
	}

	vec4::vec4(const vec4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	/* 3x3 Matrix */

	mat3::mat3()
	{
		zero();
		mat[0] = 1.0f;
		mat[4] = 1.0f;
		mat[8] = 1.0f;
	}

	mat3::mat3(const mat4& mat4)
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

	void mat3::set(float _m0, float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8)
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

	float& mat3::operator[](std::size_t index)
	{
		return mat[index];
	}

	const float& mat3::operator[](std::size_t index) const
	{
		return mat[index];
	}

	void mat3::operator=(const mat4& mat4)
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

	/* 4x4 Matrix */

	mat4::mat4()
	{
		zero();
		mat[0] = 1.0f;
		mat[5] = 1.0f;
		mat[10] = 1.0f;
		mat[15] = 1.0f;
	}

	void mat4::set(float _m0, float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8, float _m9, float _m10, float _m11, float _m12, float _m13, float _m14, float _m15)
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

	float& mat4::operator[](std::size_t index)
	{
		return mat[index];
	}

	const float& mat4::operator[](std::size_t index) const
	{
		return mat[index];
	}

	mat4 mat4::operator*(const mat4& other)
	{
		return multiply(*this, other);
	}

	/* Quaternion */

	Quaternion::Quaternion()
	{

	}

	Quaternion::Quaternion(float _x, float _y, float _z, float _w)
	{
		values.x = _x;
		values.y = _y;
		values.z = _z;
		values.w = _w;
	}

	Quaternion::Quaternion(Anemone::vec4 _values)
	{
		values = _values;
	}

	void Quaternion::scale(float s)
	{
		values *= s;
	}

	Quaternion Quaternion::conjugate()
	{
		return Quaternion(values.w, -values.x, -values.y, -values.z);
	}

	Quaternion Quaternion::inverse()
	{
		Quaternion quat = conjugate();
		quat.scale(1.0f / values.squareLength());
		return quat;
	}

	Quaternion Quaternion::unit()
	{
		Quaternion quat;
		quat.values = values;
		quat.scale(1.0f / values.length());
		return quat;
	}

	Anemone::mat4 Quaternion::getRotationMatrix()
	{
		Anemone::mat4 mat;
		mat.set(
			values.w, -values.z, values.y, values.x,
			values.z, values.w, -values.x, values.y,
			-values.y, values.x, values.w, values.z,
			-values.x, -values.y, -values.z, values.w
		);
		return multiply(mat, mat);
	}

	/* Misc Functions */
};