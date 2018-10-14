#pragma once

#include "Anemone.h"

#include <bitset>
#include <unordered_map>
#include <memory>
#include <string>

#include "Component.h"

namespace Anemone
{
	class Entity
	{
	public:

		void AddComponent(Component* component);

		template<typename T> std::shared_ptr<T> GetComponent(int bitset_id)
		{
			return std::dynamic_pointer_cast<T>(components[bitset_id]);
		}

		std::bitset<64> GetComponentBitset() const { return bitset; }

		std::shared_ptr<Entity> clone() const;
	protected:
	private:

		std::bitset<64> bitset;

		std::unordered_map<int, std::shared_ptr<Component>> components;

	};

	class EntityFactory
	{
	public:

		EntityFactory() { };

		void addEntityType(std::string entity_type_name, std::shared_ptr<Entity> entity);

	private:

		std::unordered_map<std::string, std::shared_ptr<Entity>> entity_types;

	};
};