#pragma once

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <utility>


namespace ae
{
	const double PI = 3.1415926535;

	constexpr double to_radians(double deg)
	{
		return deg * PI / 180.0;
	}

	constexpr double to_degrees(double rad)
	{
		return rad * 180.0 / PI;
	}

	// Forward Declarations
	class vec3;
	class vec4;
	class mat2;
	class mat3;
	class mat4;

	/* 2D Vector */

	class vec2
	{
	public:

		float x, y;

		constexpr vec2() : x(0.0f), y(0.0f) {}

		constexpr vec2(float _x, float _y) : x(_x), y(_y) {}

		constexpr vec2(float _v) : x(_v), y(_v) {}

		float length() const;

		float squareLength() const;

		double angle() const;

		float distance(const vec2& vec) const;

		void normalize();

		void inverse();

		vec2& operator=(const vec2& vec);

		vec2& operator=(float scalar);

		bool operator==(const vec2& vec) const;

		bool operator!=(const vec2& vec) const;

		vec2& operator+=(const vec2& vec);

		vec2& operator+=(float scalar);

		vec2& operator-=(const vec2& vec);

		vec2& operator-=(float scalar);

		vec2& operator*=(const vec2& vec);

		vec2& operator*=(float scalar);

		vec2& operator/=(const vec2& vec);

		vec2& operator/=(float scalar);

		vec2 operator+(vec2 vec) const;

		vec2 operator+(float scalar) const;

		vec2 operator-(vec2 vec) const;

		vec2 operator-(float scalar) const;

		vec2 operator-() const;

		vec2 operator*(vec2 vec) const;

		vec2 operator*(float scalar) const;

		vec2 operator/(vec2 vec) const;

		vec2 operator/(float scalar) const;

		bool operator<(float scalar) const;

		bool operator<(const vec2& vec) const;

		bool operator<=(float scalar) const;

		bool operator<=(const vec2& vec) const;

		bool operator>(float scalar) const;

		bool operator>(const vec2& vec) const;

		bool operator>=(float scalar) const;

		bool operator>=(const vec2& vec) const;

		vec2(const vec3& other);

		vec2(const vec2& other);

	};

	extern float dot(const vec2& vec1, const vec2& vec2);

	extern vec2 normalize(const vec2& vec);

	extern bool equal(const vec2& vec1, const vec2& vec2, float epsilon);

	extern vec2 rotateZ(const vec2& vec, float angle);

	extern vec2 rotateZ(const vec2& vec, double s, double c);

	extern void print(const vec2& vec);

	extern vec2 perpcw(const vec2& vec);

	extern vec2 perpccw(const vec2& vec);

	extern float cross(const vec2& v1, const vec2& v2);

	extern vec2 cross(float a, const vec2& v);

	extern vec2 cross(const vec2& v, float a);

	extern vec2 operator-(float b, const vec2& a);

	extern vec2 operator+(float b, const vec2& a);

	extern vec2 operator*(float b, const vec2& a);

	extern vec2 operator/(float b, const vec2& a);

	/* 3D Vector */

	class vec3
	{
	public:

		float x, y, z;

		constexpr vec3() : x(0.0f), y(0.0f), z(0.0f) {}

		constexpr vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

		constexpr vec3(float _v) : x(_v), y(_v), z(_v) {}

		float length() const;

		float squareLength() const;

		double angle() const;

		float distance(const vec3& vec) const;

		void normalize();

		void inverse();

		vec3& operator=(const vec3& vec);

		vec3& operator=(float scalar);

		bool operator==(const vec3& vec) const;

		bool operator!=(const vec3& vec) const;

		vec3& operator+=(const vec3& vec);

		vec3& operator+=(float scalar);

		vec3& operator-=(const vec3& vec);

		vec3& operator-=(float scalar);

		vec3& operator*=(const vec3& vec);

		vec3& operator*=(float scalar);

		vec3& operator/=(const vec3& vec);

		vec3& operator/=(float scalar);

		vec3 operator+(vec3 vec) const;

		vec3 operator+(float scalar) const;

		vec3 operator-(vec3 vec) const;

		vec3 operator-(float scalar) const;

		vec3 operator-() const;

		vec3 operator*(vec3 vec) const;

		vec3 operator*(float scalar) const;

		vec3 operator/(vec3 vec) const;

		vec3 operator/(float scalar) const;

		bool operator<(float scalar) const;

		bool operator<(const vec3& vec) const;

		bool operator<=(float scalar) const;

		bool operator<=(const vec3& vec) const;

		bool operator>(float scalar) const;

		bool operator>(const vec3& vec) const;

		bool operator>=(float scalar) const;

		bool operator>=(const vec3& vec) const;

		vec3(const vec2& other);

		vec3(const vec4& other);

		vec3(const vec3& other);

	};

	extern float dot(const vec3& vec1, const vec3& vec2);

	extern vec3 cross(const vec3& vec1, const vec3& vec2);

	extern vec3 normalize(const vec3& vec);

	extern bool equal(const vec3& vec1, const vec3& vec2, float epsilon);

	extern vec3 rotateX(const vec3& vec, float angle);

	extern vec3 rotateX(const vec3& vec, double s, double c);

	extern vec3 rotateY(const vec3& vec, float angle);

	extern vec3 rotateY(const vec3& vec, double s, double c);

	extern vec3 rotateZ(const vec3& vec, float angle);

	extern vec3 rotateZ(const vec3& vec, double s, double c);

	extern vec3 operator-(float b, const vec3& a);

	extern vec3 operator+(float b, const vec3& a);

	extern vec3 operator*(float b, const vec3& a);

	extern vec3 operator/(float b, const vec3& a);

	extern void print(const vec3& vec);

	/* 4D Vector */

	class vec4
	{
	public:

		float x, y, z, w;

		constexpr vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

		constexpr vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

		constexpr vec4(const vec3& vec, float _w) : x(vec.x), y(vec.y), z(vec.z), w(_w) {}

		constexpr vec4(const vec2& vec1, const vec2& vec2) : x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y) {}

		constexpr vec4(const vec2& vec1, float _z, float _w) : x(vec1.x), y(vec1.y), z(_z), w(_w) {}

		constexpr vec4(float _v) : x(_v), y(_v), z(_v), w(_v) {}

		float length() const;

		float squareLength() const;

		double angle() const;

		float distance(const vec4& vec) const;

		void normalize();

		void inverse();

		vec4& operator=(const vec4& vec);

		vec4& operator=(float scalar);

		bool operator==(const vec4& vec) const;

		bool operator!=(const vec4& vec) const;

		vec4& operator+=(const vec4& vec);

		vec4& operator+=(float scalar);

		vec4& operator-=(const vec4& vec);

		vec4& operator-=(float scalar);

		vec4& operator*=(const vec4& vec);

		vec4& operator*=(float scalar);

		vec4& operator/=(const vec4& vec);

		vec4& operator/=(float scalar);

		vec4 operator+(vec4 vec) const;

		vec4 operator+(float scalar) const;

		vec4 operator-(vec4 vec) const;

		vec4 operator-(float scalar) const;

		vec4 operator-() const;

		vec4 operator*(vec4 vec) const;

		vec4 operator*(float scalar) const;

		vec4 operator/(vec4 vec) const;

		vec4 operator/(float scalar) const;

		bool operator<(float scalar) const;

		bool operator<(const vec4& vec) const;

		bool operator<=(float scalar) const;

		bool operator<=(const vec4& vec) const;

		bool operator>(float scalar) const;

		bool operator>(const vec4& vec) const;

		bool operator>=(float scalar) const;

		bool operator>=(const vec4& vec) const;

		vec4(const vec2& other);

		vec4(const vec3& other);

		vec4(const vec4& other);

	};

	extern float dot(const vec4& vec1, const vec4& vec2);

	extern vec4 normalize(const vec4& vec);

	extern bool equal(const vec4& vec1, const vec4& vec2, float epsilon);

	extern vec4 operator-(float b, const vec4& a);

	extern vec4 operator+(float b, const vec4& a);

	extern vec4 operator*(float b, const vec4& a);

	extern vec4 operator/(float b, const vec4& a);

	extern void print(const vec4& vec);

	/* 2x2 Matrix */

	class mat2
	{
	public:

		mat2();

		mat2(float m1, float m2, float m3, float m4);

		void set(float _m0, float _m1, float _m2, float _m3);

		float* get() { return mat; }

		float& operator[](std::size_t index);

		const float& operator[](std::size_t index) const;

		void operator=(const mat2& other);

		ae::vec3 operator*(const ae::vec3& pos);

	private:

		float mat[4];

	};

	extern mat2 rotateZ2(float radians);

	/* 3x3 Matrix */

	class mat3
	{
	public:

		mat3();

		void set(float _m0, float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8);

		const float* get() const { return mat; }

		float* get() { return mat; }

		void zero();

		float& operator[](std::size_t index);

		const float& operator[](std::size_t index) const;

		void operator=(const mat4& mat4);

		mat3(const mat4& mat4);

	private:

		float mat[9];

	};

	extern mat3 multiply(const mat3& mat1, const mat3& mat2);

	extern vec3 multiply(const mat3& mat, const vec3& vec);

	extern mat3 transpose(const mat3& mat);

	extern void print(const mat3& mat);

	/* 4x4 Matrix */

	class mat4
	{
	public:

		mat4();

		void set(float _m0, float _m1, float _m2, float _m3, float _m4, float _m5, float _m6, float _m7, float _m8, float _m9, float _m10, float _m11, float _m12, float _m13, float _m14, float _m15);

		float* get() { return mat; }

		const float* get() const { return mat; }

		void zero();

		float& operator[](std::size_t index);

		const float& operator[](std::size_t index) const;

		mat4 operator*(const mat4& other);

		vec3 operator*(const vec3& other);

		vec4 operator*(const vec4& other);

	private:

		float mat[16];

	};

	extern mat4 identity();

	extern mat4 multiply(const mat4& mat1, const mat4& mat2);

	extern vec3 multiply(const mat4& mat, const vec3& vec);

	extern vec4 multiply(const mat4& mat, const vec4& vec);

	extern mat4 transpose(const mat4& mat);

	extern mat4 translate(float x, float y, float z);

	extern mat4 translate(const vec3& vec);

	extern mat4 scale(float x, float y, float z);

	extern mat4 scale(const vec3& s);

	extern mat4 rotateX(float radians);

	extern mat4 rotateY(float radians);

	extern mat4 rotateZ(float radians);

	extern mat4 Ortho(float left, float right, float bottom, float top, float near, float far);

	extern mat4 Ortho(float width, float height);

	extern mat4 Frustum(float left, float right, float bottom, float top, float near, float far);

	extern mat4 LookAt(vec3 eye, vec3 target, vec3 up);

	extern mat4 Perspective(float fovy, float aspect, float near, float far);

	extern void print(const mat4& mat);

	/* Quaternion */

	class Quaternion
	{
	public:

		vec4 values;

		Quaternion() { }

		Quaternion(float _x, float _y, float _z, float _w);

		Quaternion(vec4 _values);

		void scale(float s);

		Quaternion conjugate();

		Quaternion inverse();

		Quaternion unit();

		mat4 getRotationMatrix();

		const vec4& get() { return values; }

	};

	extern Quaternion multiply(const Quaternion& q1, const Quaternion& q2);

	/* Misc Functions */

	extern std::pair<bool, vec2> lineLineCollision(vec2 p1, vec2 p2, vec2 p3, vec2 p4);

	extern float triangleArea(const vec2& p1, const vec2& p2, const vec2& p3);

	extern vec2 idCoordinate(unsigned int id, unsigned int size);

	extern float normalize(float scalar);

	template<typename T>
	T lerp(T a, T b, double t)
	{
		return a + (b - a) * t;
	}

};