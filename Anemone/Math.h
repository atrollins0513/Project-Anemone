#pragma once

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <random>
#include <string>

#define PI 3.141592654f
#define to_radians(deg) (deg * PI) / 180.0f
#define to_degrees(rad) (rad * 180.0f) / PI

namespace Anemone
{

	/* Vectors */

	class vec2
	{
	public:

		float x, y;

		vec2();

		vec2(float _x, float _y);

		vec2& operator=(const vec2& vec);

		vec2& operator=(float scalar);

		bool operator==(const vec2& vec);

		bool operator!=(const vec2& vec);

		vec2& operator+=(const vec2& vec);

		vec2& operator+=(float scalar);

		vec2& operator-=(const vec2& vec);

		vec2& operator-=(float scalar);

		vec2& operator*=(const vec2& vec);

		vec2& operator*=(float scalar);

		vec2 operator+(vec2 vec);

		vec2 operator+(float scalar);

		vec2 operator-(vec2 vec);

		vec2 operator-(float scalar);

		vec2 operator*(vec2 vec);

		vec2 operator*(float scalar);

		vec2 operator/(vec2 vec);

		vec2 operator/(float scalar);

		float length() const;

		float squareLength() const;

		double angle() const;

		float distance(const vec2& vec) const;

		vec2(const vec2& other)
		{
			x = other.x;
			y = other.y;
		}
	};

	class vec3
	{
	public:

		float x, y, z;

		vec3();

		vec3(float _x, float _y, float _z);

		vec3& operator=(const vec3& vec);

		vec3& operator=(float scalar);

		bool operator==(const vec3& vec);

		bool operator!=(const vec3& vec);

		vec3& operator+=(const vec3& vec);

		vec3& operator+=(float scalar);

		vec3& operator-=(const vec3& vec);

		vec3& operator-=(float scalar);

		vec3& operator*=(const vec3& vec);

		vec3& operator*=(float scalar);

		vec3 operator+(vec3 vec);

		vec3 operator+(float scalar);

		vec3 operator-(vec3 vec);

		vec3 operator-(float scalar);

		vec3 operator*(vec3 vec);

		vec3 operator*(float scalar);

		vec3 operator/(vec3 vec);

		vec3 operator/(float scalar);

		float length() const;

		float squareLength() const;

		double angle() const;

		float distance(const vec3& vec) const;

		vec3(const vec3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
	};

	class vec4
	{
	public:

		float x, y, z, w;

		vec4();

		vec4(float _x, float _y, float _z, float _w);

		vec4(const vec3& vec, float _w);

		vec4(const vec2& vec1, const vec2& vec2);

		vec4& operator=(const vec4& vec);

		vec4& operator=(float scalar);

		bool operator==(const vec4& vec);

		bool operator!=(const vec4& vec);

		vec4& operator+=(const vec4& vec);

		vec4& operator+=(float scalar);

		vec4& operator-=(const vec4& vec);

		vec4& operator-=(float scalar);

		vec4& operator*=(const vec4& vec);

		vec4& operator*=(float scalar);

		vec4 operator+(vec4 vec);

		vec4 operator+(float scalar);

		vec4 operator-(vec4 vec);

		vec4 operator-(float scalar);

		vec4 operator*(vec4 vec);

		vec4 operator*(float scalar);

		vec4 operator/(vec4 vec);

		vec4 operator/(float scalar);

		float length() const;

		float squareLength() const;

		double angle() const;

		float distance(const vec4& vec) const;

		vec4(const vec4& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}
	};

	/* Matrices */

	class mat4
	{
	public:

		mat4();

		void set(float _m0, float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8, float _m9, float _m10, float _m11, float _m12, float _m13, float _m14, float _m15);

		float* get() { return mat; }

		void zero();

		float& operator[](std::size_t index);

		const float& operator[](std::size_t index) const;

		mat4 operator*(const mat4& other);

	private:

		float mat[16];

	};

	class mat3
	{
	public:

		mat3();

		void set(float _m0, float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8);

		float* get() { return mat; }

		void zero();

		float& operator[](std::size_t index);

		const float& operator[](std::size_t index) const;

		void operator=(const mat4& mat4);

		mat3(const mat4& mat4);

	private:

		float mat[9];

	};

	/* Quaternion */

	class Quaternion
	{
	public:

		Anemone::vec4 values;

		Quaternion();

		Quaternion(float _x, float _y, float _z, float _w);

		Quaternion(Anemone::vec4 _values);

		void scale(float s);

		Quaternion conjugate();

		Quaternion inverse();

		Quaternion unit();

		Anemone::mat4 getRotationMatrix();

		const Anemone::vec4& get() { return values; }

	};

	/* 2D Vector */

	extern float dot(const vec2& vec1, const vec2& vec2);

	extern vec2 normalize(const vec2& vec);

	extern bool equal(const vec2& vec1, const vec2& vec2, float epsilon);

	extern vec2 rotateZ(const vec2& vec, float angle);

	extern void print(const vec2& vec);

	/* 3D Vector */

	extern float dot(const vec3& vec1, const vec3& vec2);

	extern vec3 cross(const vec3& vec1, const vec3& vec2);

	extern vec3 normalize(const vec3& vec);

	extern bool equal(const vec3& vec1, const vec3& vec2, float epsilon);

	extern vec3 rotateX(const vec3& vec, float angle);

	extern vec3 rotateY(const vec3& vec, float angle);

	extern vec3 rotateZ(const vec3& vec, float angle);

	extern void print(const vec3& vec);

	/* 4D Vector */

	extern float dot(const vec4& vec1, const vec4& vec2);

	extern vec4 normalize(const vec4& vec);

	extern bool equal(const vec4& vec1, const vec4& vec2, float epsilon);

	extern void print(const vec4& vec);

	/* 3x3 Matrix */

	extern mat3 multiply(const mat3& mat1, const mat3& mat2);

	extern vec3 multiply(const mat3& mat, const vec3& vec);

	extern mat3 transpose(const mat3& mat);

	extern void print(const mat3& mat);

	/* 4x4 Matrix */

	extern mat4 identity();

	extern mat4 multiply(const mat4& mat1, const mat4& mat2);

	extern vec3 multiply(const mat4& mat, const vec3& vec);

	extern vec4 multiply(const mat4& mat, const vec4& vec);

	extern mat4 transpose(const mat4& mat);

	extern mat4 translate(float x, float y, float z);

	extern mat4 scale(float x, float y, float z);

	extern mat4 rotateX(float radians);

	extern mat4 rotateY(float radians);

	extern mat4 rotateZ(float radians);

	extern mat4 Ortho(float left, float right, float bottom, float top, float near, float far);

	extern mat4 Frustum(float left, float right, float bottom, float top, float near, float far);

	extern mat4 LookAt(vec3 eye, vec3 target, vec3 up);

	extern mat4 Perspective(float fovy, float aspect, float near, float far);

	extern void print(const mat4& mat);

	/* Quaternion */

	extern Quaternion multiply(const Quaternion& q1, const Quaternion& q2);

	/* Misc Functions */

	extern void SetSeed(int seed);

	extern int random(unsigned int upper_limit);

	extern int random(unsigned int lower_limit, unsigned int upper_limit);

	extern vec3 hexToRGB(std::string hex);

};