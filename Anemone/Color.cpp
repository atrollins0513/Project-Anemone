#include "Color.h"

namespace Anemone
{
	Color::Color()
	{
		r = g = b = a = 1.0f;
	}

	Color::Color(AE_FLOAT _r, AE_FLOAT _g, AE_FLOAT _b, AE_FLOAT _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	void Color::Invert()
	{
		r = 1.0f - r;
		g = 1.0f - g;
		b = 1.0f - b;
	}

	void Color::BlackAndWhite()
	{
		AE_FLOAT avg = (r + g + b) / 3.0f;
		r = g = b = avg;
	}

	Color Color::Blend(const Color& other)
	{
		Color newColor;
		newColor.r = (r + other.r) / 2.0f;
		newColor.g = (g + other.g) / 2.0f;
		newColor.b = (b + other.b) / 2.0f;
		return newColor;
	}
};