#pragma once

#include "Anemone.h"

#include <bitset>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

namespace Anemone
{
	class System
	{
	public:

		virtual void init() = 0;

		virtual void update(AE_DOUBLE dt) = 0;

		bool AddEntity(std::shared_ptr<Entity> entity);

		template<typename T> void AddComponent()
		{
			T comp;
			bitset[comp.BitSetIndex()];
		}

	protected:

		std::bitset<64> bitset;

		std::vector<std::shared_ptr<Entity>> entities;

	private:
	};
};