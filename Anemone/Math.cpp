#include "Math.h"

namespace Anemone
{
	namespace Math
	{
		void SetSeed(int seed)
		{
			srand(seed);
		}

		AE_INT random(AE_UINT upper_limit)
		{
			return rand() % upper_limit;
		}

		AE_INT random(AE_UINT lower_limit, AE_UINT upper_limit)
		{
			return rand() % upper_limit + lower_limit;
		}
	};
};