#pragma once

#include <memory>
#include <bitset>
#include <vector>
#include <array>

#if !defined(AE_MAX_COMPONENTS)
#define AE_MAX_COMPONENTS 32
#endif

namespace ae
{
	namespace ECS
	{
		struct Component {};
		using ComponentID = std::size_t;
		constexpr std::size_t maxComponents{ AE_MAX_COMPONENTS };
		using ComponentBitSet = std::bitset<maxComponents>;
		using ComponentArray = std::array<Component*, maxComponents>;

		namespace Internal
		{
			inline ComponentID getUniqueComponentID() noexcept
			{
				static ComponentID lastID{ 0u };
				return lastID++;
			}
		}

		template<typename T>
		inline ComponentID getComponentTypeID() noexcept
		{
			static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
			static ComponentID typeID{ Internal::getUniqueComponentID() };
			return typeID;
		}

		class Entity
		{
		public:
			template<typename T, typename... TArgs>
			T* AddComponent(TArgs&&... mArgs)
			{
				assert(!hasComponent<T>());
				auto c = new T(std::forward<TArgs>(mArgs)...);
				components[getComponentTypeID<T>()] = c;
				bitset[getComponentTypeID<T>()] = true;
				return c;
			}

			template<typename T> T* get() const
			{
				assert(hasComponent<T>());
				return static_cast<T*>(components[getComponentTypeID<T>()]);
			}

			template<typename T> bool hasComponent() const
			{
				return bitset[getComponentTypeID<T>()];
			}

			bool hasRequiredComponents(const ComponentBitSet& systemBitSet) const
			{
				return (bitset & systemBitSet) == systemBitSet;
			}

			~Entity()
			{
				for (auto c : components)
				{
					if (c != nullptr)
					{
						delete c;
					}
				}
			}
		private:
			ComponentArray components;
			ComponentBitSet bitset;
		};

		inline ComponentBitSet makeBitSet(std::initializer_list<ComponentID> components)
		{
			ComponentBitSet bits;
			for (auto c : components)
			{
				bits.set(c);
			}
			return bits;
		};

		class System
		{
		public:

			System() { }

			bool addEntity(ECS::Entity* e)
			{
				if (e->hasRequiredComponents(bits))
				{
					entities.push_back(e);
					return true;
				}
				return false;
			}

			virtual void update(ECS::Entity* e, double dt) { };

			void work(double dt)
			{
				for (auto it = entities.begin(); it != entities.end();)
				{
					if ((*it))
					{
						update((*it), dt);
						++it;
					}
					else
					{
						it = entities.erase(it);
					}
				}
			}

			template<typename T>
			void setRequiredComponents()
			{
				bits.set(ECS::getComponentTypeID<T>());
			}

			template<typename T, typename F, typename ...Args>
			void setRequiredComponents()
			{
				bits.set(ECS::getComponentTypeID<T>());
				setRequiredComponents<F, Args...>();
			}

		protected:

			std::vector<ECS::Entity*> entities;

			ECS::ComponentBitSet bits;

		};

	};
};