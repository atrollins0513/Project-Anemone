#include "Entity.h"

void Anemone::Entity::AddComponent(Component* component)
{
	if (bitset[component->BitSetIndex()] != 1)
	{
		component->entity = this;
		components[component->BitSetIndex()] = component;
	}
}

Anemone::Entity::~Entity()
{
	for (auto c : components)
	{
		if (c.second)
			delete c.second;
	}
}