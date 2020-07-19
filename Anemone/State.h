#pragma once

#include <memory>
#include <unordered_map>
#include <tuple>
#include <assert.h>
#include <string>

#ifndef GLEW_STATIC
	#define GLEW_STATIC
#endif

#include "includes\glew.h"
#include "includes\glfw3.h"

#include "Utilities.h"
#include "Event.h"

namespace ae
{
	class Window;

	class State
	{
	public:

		virtual void init() = 0;

		virtual void update(double dt) = 0;

		virtual void render(double alpha) = 0;

		virtual void event(ae::Event& e) = 0;

		virtual void destroy() = 0;

		virtual std::string getName() = 0;

		void setParent(Window* _parent) { parent = _parent; }

		Window* getParent() { return parent; }

	protected:

		Window* parent;

	};
	
	class StateManager
	{
	public:

		StateManager() : current_state(nullptr), parent(nullptr) { }

		template<typename T, typename ... Args>
		bool addState(Args&& ... args)
		{
			static_assert(std::is_base_of<State, T>::value, "T must inherit from State");

			sptr<T> newState = makeShared<T>(std::forward<Args>(args)...);
			newState->setParent(parent);

			assert(newState->getName() != "");
			assert(!stateExists(newState->getName()));

			states.emplace(newState->getName(), newState);

		}

		void addState(sptr<State> state);

		void removeState(const std::string& name);

		void setState(const std::string& name, bool initialize = false);

		sptr<State> getState(const std::string& name);

		sptr<State> getCurrentState();

		bool stateExists(const std::string& name);

		void setStateManagerParent(Window* _parent) { parent = _parent; }

		friend Window;

	protected:

		sptr<State> current_state;

		std::unordered_map<std::string, sptr<State>> states;

	private:

		Window* parent;

	};

};