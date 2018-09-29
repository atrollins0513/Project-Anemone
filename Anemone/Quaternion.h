#pragma once

#include "Anemone.h"
#include "Math.h"

namespace Anemone
{
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
	protected:
	private:
	};

	namespace Math
	{
		Quaternion multiply(const Quaternion& q1, const Quaternion& q2)
		{
			return Quaternion(
				q1.values.w*q2.values.w - q1.values.x*q2.values.x - q1.values.y*q2.values.y - q1.values.z*q2.values.z,
				q1.values.w*q2.values.x + q1.values.x*q2.values.w + q1.values.y*q2.values.z - q1.values.z*q2.values.y,
				q1.values.w*q2.values.y + q1.values.y*q2.values.w + q1.values.z*q2.values.x - q1.values.x*q2.values.z,
				q1.values.w*q2.values.z + q1.values.z*q2.values.w + q1.values.x*q2.values.y - q1.values.y*q2.values.x);
		}
	};
};