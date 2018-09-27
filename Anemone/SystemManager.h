#pragma once

#include "Anemone.h"

#include <vector>
#include <memory>

#include "System.h"
#include "Entity.h"

namespace Anemone
{
	namespace Manager
	{
		class SystemManager
		{
		public:

			SystemManager();

			void AddSytem(std::shared_ptr<System> system);

			void AddEntity(Entity* entity);

			void Update(AE_DOUBLE dt);

		protected:
		private:

			std::vector <std::shared_ptr<System>> systems;

		};
	};
};
