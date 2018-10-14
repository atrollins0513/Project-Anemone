#pragma once

#include "Anemone.h"

namespace Anemone
{
	class Entity;

	struct Component
	{

		Entity* entity;

		virtual AE_INT BitSetIndex() const = 0;

	};
};