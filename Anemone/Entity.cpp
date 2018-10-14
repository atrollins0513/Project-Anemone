#include "Entity.h"

namespace Anemone
{
	// Entity
	void Entity::AddComponent(Component* component)
	{
		if (bitset[component->BitSetIndex()] != 1)
		{
			std::shared_ptr<Component> c{ component };
			c->entity = this;
			components[c->BitSetIndex()] = c;
		}
	}

	std::shared_ptr<Entity> Entity::clone() const
	{
		return std::shared_ptr<Entity>(new Entity(*this));
	}

	// EntityFactory

	void EntityFactory::addEntityType(std::string entity_type_name, std::shared_ptr<Entity> entity)
	{
		entity_types[entity_type_name] = entity;
	}
};