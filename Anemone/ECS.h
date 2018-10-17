#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>

namespace Anemone
{
	namespace ECS
	{

		// Component Base Structure
		struct Component
		{

		};

		// Systems
		struct System
		{
			virtual void update(double dt) = 0;
		};

		namespace
		{

			unsigned int id_counter = 0;

			std::vector<unsigned int> retired_ids;

			std::unordered_map < std::type_index, std::unordered_map<unsigned int, std::shared_ptr<Component>>> components;

			inline unsigned int getNewID()
			{
				if (retired_ids.size() == 0)
				{
					return ++id_counter;
				}
				else
				{
					unsigned int id = retired_ids.back();
					retired_ids.pop_back();
					return id;
				}
			}

		};

		template <typename T>
		auto& getComponentList()
		{
			return components[typeid(T)];
		}

		class Entity
		{
		public:
			Entity()
			{
				id = getNewID();
			}

			template<typename T, typename... TArgs>
			std::shared_ptr<T> add(TArgs&&... mArgs)
			{
				std::shared_ptr<T> c = std::make_shared<T>(std::forward<TArgs>(mArgs)...);
				components[typeid(T)][id] = c;
				return c;
			}

			template<typename T>
			bool has()
			{
				return (components[typeid(T)][id] != nullptr);
			}

			template<typename T>
			T& get()
			{
				assert(has<T>());
				return *static_cast<T*>(components[typeid(T)][id]);
			}

			const unsigned int getID() const
			{
				return id;
			}
		private:
			unsigned int id;
		};
	};
};
