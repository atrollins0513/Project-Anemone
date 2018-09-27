#pragma once

#include "Anemone.h"
#include "Quaternion.h"

namespace Anemone
{
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

	Quaternion::Quaternion(ae::vec4 _values)
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

	ae::mat4 Quaternion::getRotationMatrix()
	{
		ae::mat4 mat;
		mat.set(
			values.w, -values.z, values.y, values.x,
			values.z, values.w, -values.x, values.y,
			-values.y, values.x, values.w, values.z,
			-values.x, -values.y, -values.z, values.w
		);
		return aem::multiply(mat, mat);
	}
};