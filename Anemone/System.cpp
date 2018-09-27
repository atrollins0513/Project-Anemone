#include "System.h"

Anemone::AE_BOOL Anemone::System::CompatiableEntity(Entity* entity)
{
	return (bitset == entity->GetComponentBitset());
}

bool Anemone::System::AddEntity(Entity* entity)
{
	if (CompatiableEntity(entity))
	{
		entities.push_back(entity);
		return true;
	}
	return false;
}