#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <memory>
#include <unordered_map>
#include <tuple>

#include "includes\glew.h"
#include "includes\glfw3.h"

namespace Anemone
{
	class Window;

	class State
	{
	public:

		virtual void Init() = 0;

		virtual void Update(double dt) = 0;

		virtual void Render(double alpha) = 0;

		virtual void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {}
		
		virtual void CharEvent(GLFWwindow* window, unsigned int codepoint) {}
		
		virtual void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos) {}

		virtual void MouseClickEvent(GLFWwindow* window, int button, int action, int mods) {}
		
		virtual void ScrollEvent(GLFWwindow* window, double xoffset, double yoffset) {}
		
		virtual void MouseEnterEvent(GLFWwindow* window, int entered) {}

		virtual void JoystickEvent(int joy, int ev) {}

		virtual void Destroy() = 0;
		
		virtual void TransitionOut(unsigned int _transition_state_id) {}

		virtual void TransitionIn() {}

		void setID(unsigned int _id) { id = _id; }

		void setParentWindow(std::shared_ptr<Window> parent)
		{
			parent_window = parent;
		}

		std::shared_ptr<Window> getParentWindow()
		{
			return parent_window;
		}

	protected:

		unsigned int id;

		bool transition_in, transition_out;

		unsigned int transition_state_id;

		std::shared_ptr<Window> parent_window;

	};

	namespace StateManager
	{

		namespace
		{

			extern unsigned int current_state;

			extern std::unordered_map<unsigned int, std::shared_ptr<State>> states;

		};

		extern void Init();

		extern void Update(double dt);

		extern void Render(double alpha);

		extern void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

		extern void CharEvent(GLFWwindow* window, unsigned int codepoint);

		extern void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos);

		extern void MouseClickEvent(GLFWwindow* window, int button, int action, int mods);

		extern void ScrollEvent(GLFWwindow* window, double xoffset, double yoffset);

		extern void MouseEnterEvent(GLFWwindow* window, int entered);

		extern void JoystickEvent(int joy, int ev);

		extern void Destroy();

		extern bool AddState(unsigned int id, std::shared_ptr<State> state);

		extern void SetState(unsigned int id, bool initialize = false, bool transitionIn = false);

		extern std::shared_ptr<State> GetState(unsigned int id);

		extern std::shared_ptr<State> GetCurrentState();

		extern void RemoveState(unsigned int id);

		extern bool StateExists(unsigned int id);

		class Window;

		template<typename T>
		inline std::shared_ptr<T> CreateState(unsigned int id, std::shared_ptr<Anemone::Window> parent, bool setCurrent = false, bool initialize = false, bool transitionIn = false)
		{
			static_assert(std::is_base_of<State, T>::value, "T must be derived from State");

			auto newState = std::make_shared<T>();
			newState->setParentWindow(parent);
			bool added = AddState(id, newState);

			if (added && setCurrent)
			{
				SetState(id, initialize, transitionIn);
				return newState;
			}

			return nullptr;
		}
	};

};