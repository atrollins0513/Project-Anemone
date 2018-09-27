#pragma once

#include "Component.h"

#include "vec3.h"

namespace Anemone
{
	namespace Components
	{
		struct PositionComponent : public Component
		{
			Anemone::vec3 pos;
			AE_INT width, height;
			AE_INT BitSetIndex() const
			{
				return 0;
			}
		};
	};
};