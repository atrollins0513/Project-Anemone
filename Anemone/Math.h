#pragma once

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <random>
#include <string>

#include "Anemone.h"

#define PI 3.141592654f
#define to_radians(deg) (deg * PI) / 180.0f
#define to_degrees(rad) (rad * 180.0f) / PI

namespace Anemone
{

	/* Vectors */

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
	};

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
	};

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
	};

	/* Matrices */

	class mat4
	{
	public:

		mat4();

		void set(AE_FLOAT _m0, AE_FLOAT _m1, AE_FLOAT _m2, AE_FLOAT _m3, AE_FLOAT _m4, AE_FLOAT _m5, AE_FLOAT _m6, AE_FLOAT _m7, AE_FLOAT _m8, AE_FLOAT _m9, AE_FLOAT _m10, AE_FLOAT _m11, AE_FLOAT _m12, AE_FLOAT _m13, AE_FLOAT _m14, AE_FLOAT _m15);

		AE_FLOAT* get() { return mat; }

		void zero();

		AE_FLOAT& operator[](std::size_t index);

		const AE_FLOAT& operator[](std::size_t index) const;

		mat4 operator*(const mat4& other);

	private:

		AE_FLOAT mat[16];

	};

	class mat3
	{
	public:

		mat3();

		void set(AE_FLOAT _m0, AE_FLOAT _m1, AE_FLOAT _m2, AE_FLOAT _m3, AE_FLOAT _m4, AE_FLOAT _m5, AE_FLOAT _m6, AE_FLOAT _m7, AE_FLOAT _m8);

		AE_FLOAT* get() { return mat; }

		void zero();

		AE_FLOAT& operator[](std::size_t index);

		const AE_FLOAT& operator[](std::size_t index) const;

		void operator=(const mat4& mat4);

		mat3(const mat4& mat4);

	private:

		AE_FLOAT mat[9];

	};

	/* Quaternion */

	class Quaternion
	{
	public:

		ae::vec4 values;

		Quaternion();

		Quaternion(float _x, float _y, float _z, float _w);

		Quaternion(ae::vec4 _values);

		void scale(float s);

		Quaternion conjugate();

		Quaternion inverse();

		Quaternion unit();

		ae::mat4 getRotationMatrix();

		const ae::vec4& get() { return values; }

	};

	/* 2D Vector */

	extern AE_FLOAT dot(const vec2& vec1, const vec2& vec2);

	extern vec2 normalize(const vec2& vec);

	extern AE_BOOL equal(const vec2& vec1, const vec2& vec2, float epsilon);

	extern vec2 rotateZ(const vec2& vec, float angle);

	extern void print(const vec2& vec);

	/* 3D Vector */

	extern AE_FLOAT dot(const vec3& vec1, const vec3& vec2);

	extern vec3 cross(const vec3& vec1, const vec3& vec2);

	extern vec3 normalize(const vec3& vec);

	extern AE_BOOL equal(const vec3& vec1, const vec3& vec2, float epsilon);

	extern vec3 rotateX(const vec3& vec, float angle);

	extern vec3 rotateY(const vec3& vec, float angle);

	extern vec3 rotateZ(const vec3& vec, float angle);

	extern void print(const vec3& vec);

	/* 4D Vector */

	extern AE_FLOAT dot(const vec4& vec1, const vec4& vec2);

	extern vec4 normalize(const vec4& vec);

	extern AE_BOOL equal(const vec4& vec1, const vec4& vec2, float epsilon);

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

	extern mat4 translate(AE_FLOAT x, AE_FLOAT y, AE_FLOAT z);

	extern mat4 scale(AE_FLOAT x, AE_FLOAT y, AE_FLOAT z);

	extern mat4 rotateX(AE_FLOAT radians);

	extern mat4 rotateY(AE_FLOAT radians);

	extern mat4 rotateZ(AE_FLOAT radians);

	extern mat4 Ortho(AE_FLOAT left, AE_FLOAT right, AE_FLOAT bottom, AE_FLOAT top, AE_FLOAT near, AE_FLOAT far);

	extern mat4 Frustum(AE_FLOAT left, AE_FLOAT right, AE_FLOAT bottom, AE_FLOAT top, AE_FLOAT near, AE_FLOAT far);

	extern mat4 LookAt(vec3 eye, vec3 target, vec3 up);

	extern mat4 Perspective(AE_FLOAT fovy, AE_FLOAT aspect, AE_FLOAT near, AE_FLOAT far);

	extern void print(const mat4& mat);

	/* Quaternion */

	extern Quaternion multiply(const Quaternion& q1, const Quaternion& q2);

	/* Misc Functions */

	extern void SetSeed(AE_INT seed);

	extern AE_INT random(AE_UINT upper_limit);

	extern AE_INT random(AE_UINT lower_limit, AE_UINT upper_limit);

	extern vec3 hexToRGB(std::string hex);

};