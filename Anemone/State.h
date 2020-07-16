#pragma once

#include <memory>
#include <unordered_map>
#include <tuple>
#include <assert.h>

#ifndef GLEW_STATIC
	#define GLEW_STATIC
#endif

#include "includes\glew.h"
#include "includes\glfw3.h"

namespace ae
{
	class Window;

	class State
	{
	public:

		virtual void init() = 0;

		virtual void update(double dt) = 0;

		virtual void render(double alpha) = 0;

		virtual void destroy() = 0;

		virtual void keyEvent(int key, int scancode, int action, int mods) {}
		
		virtual void charEvent(unsigned int codepoint) {}
		
		virtual void mouseMoveEvent(double xpos, double ypos) {}

		virtual void mouseClickEvent(int button, int action, int mods) {}
		
		virtual void scrollEvent(double xoffset, double yoffset) {}
		
		virtual void mouseEnterEvent(int entered) {}

		virtual void joystickEvent(int joy, int ev) {}

		virtual void transitionOut(unsigned int _transition_state_id) {}

		virtual void transitionIn() {}

		void setID(unsigned int _id) { id = _id; }

		void setParent(Window* _parent) { parent = _parent; }

		Window* getParent() { return parent; }

	protected:

		unsigned int id;

		bool transition_in, transition_out;

		unsigned int transition_state_id;

		Window* parent;

	};
	
	class StateManager
	{
	public:

		StateManager() : current_state(nullptr), parent(nullptr) { }

		template<typename T>
		bool addState(unsigned int id)
		{
			static_assert(std::is_base_of<State, T>::value, "T must inherit from State");
			assert(states.find(id) != states.end()); // Throws if state id already exists

			std::shared_ptr<T> newState = std::make_shared<T>();
			newState->setParent(parent);

			states.emplace(id, newState);
		}

		void removeState(unsigned int id);

		void setState(unsigned int id, bool initialize = false, bool transitionIn = false);

		std::shared_ptr<State> getState(unsigned int id);

		std::shared_ptr<State> getCurrentState();

		bool stateExists(unsigned int id);

		friend Window;

	private:

		std::shared_ptr<State> current_state;

		std::unordered_map<int, std::shared_ptr<State>> states;

		Window* parent;

	};

};