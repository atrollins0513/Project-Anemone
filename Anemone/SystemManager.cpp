#include "SystemManager.h"

namespace Anemone
{
	namespace Manager
	{
		SystemManager::SystemManager()
		{

		}

		void SystemManager::AddSytem(std::shared_ptr<System> system)
		{
			systems.push_back(system);
		}

		void SystemManager::AddEntity(Entity* entity)
		{
			for (auto s : systems)
			{
				s->AddEntity(entity);
			}
		}

		void SystemManager::Update(AE_DOUBLE dt)
		{
			for (auto s : systems)
			{
				s->Update(dt);
			}
		}
	};
};