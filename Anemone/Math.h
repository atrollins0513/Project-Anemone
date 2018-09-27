#pragma once

#include "Anemone.h"

#include <stdlib.h>
#include <math.h>
#include <algorithm>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

#define PI 3.1415937f
#define to_radians(deg) (deg * PI) / 180.0f
#define to_degrees(rad) (rad * 180.0f) / PI

namespace Anemone
{
	namespace Math
	{

		extern void SetSeed(int seed);

		extern AE_INT random(AE_UINT upper_limit);

		extern AE_INT random(AE_UINT lower_limit, AE_UINT upper_limit);

	};
};

#ifndef aem
#define aem Anemone::Math
#endif