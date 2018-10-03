#include "StateManager.h"

namespace Anemone
{
	namespace StateManager
	{
		namespace
		{
			AE_UINT current_state = 0;
			std::unordered_map<AE_UINT, std::shared_ptr<State>> states;
			std::unordered_map<AE_UINT, AE_BOOL> initialization_list;
		};

		void Init()
		{
			if (states[current_state] != nullptr)
				states[current_state]->Init();
		}

		void Update(AE_DOUBLE dt)
		{
			states[current_state]->Update(dt);
		}

		void Render(AE_DOUBLE alpha)
		{
			states[current_state]->Render(alpha);
		}

		void KeyEvent(GLFWwindow* window, AE_INT key, AE_INT scancode, AE_INT action, AE_INT mods)
		{
			states[current_state]->KeyEvent(window, key, scancode, action, mods);
		}

		void CharEvent(GLFWwindow* window, AE_UINT codepoint)
		{
			states[current_state]->CharEvent(window, codepoint);
		}

		void MouseMoveEvent(GLFWwindow* window, AE_DOUBLE xpos, AE_DOUBLE ypos)
		{
			states[current_state]->MouseMoveEvent(window, xpos, ypos);
		}

		void MouseClickEvent(GLFWwindow* window, AE_INT button, AE_INT action, AE_INT mods)
		{
			states[current_state]->MouseClickEvent(window, button, action, mods);
		}

		void ScrollEvent(GLFWwindow* window, AE_DOUBLE xoffset, AE_DOUBLE yoffset)
		{
			states[current_state]->ScrollEvent(window, xoffset, yoffset);
		}

		void MouseEnterEvent(GLFWwindow* window, AE_INT entered)
		{
			states[current_state]->MouseEnterEvent(window, entered);
		}

		void JoystickEvent(AE_INT joy, AE_INT ev)
		{
			states[current_state]->JoystickEvent(joy, ev);
		}

		void Destroy()
		{
			if (states[current_state] != nullptr)
				states[current_state]->Destroy();
		}

		void AddState(AE_UINT id, std::shared_ptr<State> state)
		{
			if (state != nullptr)
			{
				state->SetID(id);
				states[id] = state;
				initialization_list[id] = false;
			}
		}

		void SetState(AE_UINT id, AE_BOOL transition_in)
		{
			if (states[id] != nullptr)
			{
				current_state = id;

				if (initialization_list[current_state] == false)
				{
					states[current_state]->Init();
					initialization_list[current_state] = true;
				}

				if (transition_in)
				{
					states[current_state]->TransitionIn();
				}
			}
		}

		std::shared_ptr<State> GetState(AE_UINT id)
		{
			if (states[id] != nullptr)
				return states[id];
			else
				return nullptr;
		}

		std::shared_ptr<State> GetCurrentState()
		{
			return states[current_state];
		}

		void RemoveState(AE_UINT id)
		{
			if (states[id] != nullptr)
			{
				states.erase(id);
				initialization_list.erase(id);
			}
		}
	};
};