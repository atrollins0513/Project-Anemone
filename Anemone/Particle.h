#pragma once

#include "Anemone.h"

#include "vec3.h"
#include "Color.h"

namespace Anemone
{
	struct Particle
	{
		vec3 pos, vel;

		AE_FLOAT width, height;

		AE_FLOAT u, v, u_width, v_height;

		Color color;

		AE_DOUBLE age;

		AE_DOUBLE life_limit;

		Particle()
		{
			width = height = 0.0f;
			u = v = u_width, v_height = 0.0f;
			color = Color(1.0f, 1.0f, 1.0f, 1.0f);
			age = 0.0;
		}

		Particle(AE_FLOAT _width, AE_FLOAT _height, AE_FLOAT _u, AE_FLOAT _v, AE_FLOAT _u_width, AE_FLOAT _v_height, Color _color, AE_DOUBLE _life_limit)
		{
			width = _width;
			height = _height;
			u = _u;
			v = _v;
			u_width = _u_width;
			v_height = _v_height;
			color = _color;
			life_limit = _life_limit;
			age = 0.0;
		}
	};
};
