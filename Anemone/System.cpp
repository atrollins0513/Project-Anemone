#include "System.h"

bool Anemone::System::AddEntity(std::shared_ptr<Entity> entity)
{
	if ((bitset & entity->GetComponentBitset()) == bitset)
	{
		entities.push_back(entity);
		return true;
	}
	return false;
}