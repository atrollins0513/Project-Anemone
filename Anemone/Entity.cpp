#include "Entity.h"

void Anemone::Entity::AddComponent(Component* component)
{
	if (bitset[component->BitSetIndex()] != 1)
	{
		std::shared_ptr<Component> c{ component };
		c->entity = this;
		components[c->BitSetIndex()] = c;
	}
}