#pragma once

#include "Anemone.h"

namespace Anemone
{
	class Color
	{
	public:

		AE_FLOAT r, g, b, a;

		Color();

		Color(AE_FLOAT _r, AE_FLOAT _g, AE_FLOAT _b, AE_FLOAT _a);

		void Invert();

		void BlackAndWhite();

		Color Blend(const Color& other);

	protected:
	private:
	};
};
