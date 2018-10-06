#pragma once

#include "Anemone.h"

#include "includes\glew.h"
#include "includes\glfw3.h"

namespace Anemone
{
	class Window;

	class State
	{
	public:

		virtual void Init() = 0;

		virtual void Update(AE_DOUBLE dt) = 0;

		virtual void Render(AE_DOUBLE alpha) = 0;

		virtual void KeyEvent(GLFWwindow* window, AE_INT key, AE_INT scancode, AE_INT action, AE_INT mods) {}
		
		virtual void CharEvent(GLFWwindow* window, AE_UINT codepoint) {}
		
		virtual void MouseMoveEvent(GLFWwindow* window, AE_DOUBLE xpos, AE_DOUBLE ypos) {}

		virtual void MouseClickEvent(GLFWwindow* window, AE_INT button, AE_INT action, AE_INT mods) {}
		
		virtual void ScrollEvent(GLFWwindow* window, AE_DOUBLE xoffset, AE_DOUBLE yoffset) {}
		
		virtual void MouseEnterEvent(GLFWwindow* window, AE_INT entered) {}

		virtual void JoystickEvent(AE_INT joy, AE_INT ev) {}

		virtual void Destroy() = 0;
		
		virtual void TransitionOut(AE_UINT _transition_state_id) = 0;

		virtual void TransitionIn() = 0;

		void SetID(AE_UINT _id) { id = _id; }

		void setParentWindow(std::shared_ptr<Window> parent)
		{
			parent_window = parent;
		}

		std::shared_ptr<Window> getParentWindow()
		{
			return parent_window;
		}

	protected:

		AE_UINT id;

		AE_BOOL transition_in, transition_out;

		AE_UINT transition_state_id;

		std::shared_ptr<Window> parent_window;

	};

};