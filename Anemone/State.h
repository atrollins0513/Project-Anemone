#pragma once

#include "Anemone.h"

#include <gl\glew.h>
#include <gl\glfw3.h>

namespace Anemone
{

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

		virtual void Destroy() = 0;

		
		virtual void TransitionOut(unsigned int _transition_state_id) = 0;

		virtual void TransitionIn() = 0;


		void SetID(AE_UINT _id) { id = _id; }

	protected:
	private:

		AE_UINT id;

		AE_BOOL transition_in, transition_out;

		AE_UINT transition_state_id;

	};

};