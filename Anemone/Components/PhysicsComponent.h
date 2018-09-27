#pragma once

#include "Component.h"

#include "vec3.h"

namespace Anemone
{
	namespace Components
	{
		struct PhysicsComponent : public Component
		{
			Anemone::vec3 vel, accel;
			AE_FLOAT mass, force;
		};
	};
};