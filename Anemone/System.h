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
		virtual void Init() = 0;
		virtual void Update(AE_DOUBLE dt) = 0;

		AE_BOOL CompatiableEntity(Entity* entity);
		virtual bool AddEntity(Entity* entity);

		template<typename T>
		void AddComponent()
		{
			T comp;
			bitset[comp.BitSetIndex()];
		}
	protected:
		std::bitset<64> bitset;
		std::vector<Entity*> entities;
	private:
	};
};