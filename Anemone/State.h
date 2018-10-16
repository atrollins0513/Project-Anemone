#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "includes\glew.h"
#include "includes\glfw3.h"

#include "Anemone.h"

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

		void SetID(unsigned int _id) { id = _id; }

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

};