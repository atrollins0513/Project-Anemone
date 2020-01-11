#include "State.h"

namespace Anemone
{

	namespace StateManager
	{

		namespace
		{
			AE_UINT current_state = 0;
			std::unordered_map<AE_UINT, std::shared_ptr<State>> states;
		};

		void Init()
		{
			if (StateExists(current_state))
			{
				if (states.at(current_state) != nullptr)
				{
					states.at(current_state)->Init();
				}
			}
		}

		void Update(AE_DOUBLE dt)
		{
			states.at(current_state)->Update(dt);
		}

		void Render(AE_DOUBLE alpha)
		{
			states.at(current_state)->Render(alpha);
		}

		void KeyEvent(GLFWwindow * window, AE_INT key, AE_INT scancode, AE_INT action, AE_INT mods)
		{
			states.at(current_state)->KeyEvent(window, key, scancode, action, mods);
		}

		void CharEvent(GLFWwindow * window, AE_UINT codepoint)
		{
			states.at(current_state)->CharEvent(window, codepoint);
		}

		void MouseMoveEvent(GLFWwindow * window, AE_DOUBLE xpos, AE_DOUBLE ypos)
		{
			states.at(current_state)->MouseMoveEvent(window, xpos, ypos);
		}

		void MouseClickEvent(GLFWwindow * window, AE_INT button, AE_INT action, AE_INT mods)
		{
			states.at(current_state)->MouseClickEvent(window, button, action, mods);
		}

		void ScrollEvent(GLFWwindow * window, AE_DOUBLE xoffset, AE_DOUBLE yoffset)
		{
			states.at(current_state)->ScrollEvent(window, xoffset, yoffset);
		}

		void MouseEnterEvent(GLFWwindow * window, AE_INT entered)
		{
			states.at(current_state)->MouseEnterEvent(window, entered);
		}

		void JoystickEvent(AE_INT joy, AE_INT ev)
		{
			states.at(current_state)->JoystickEvent(joy, ev);
		}

		void Destroy()
		{
			if (StateExists(current_state))
			{
				if (states.at(current_state) != nullptr)
				{
					states.at(current_state)->Destroy();
				}
			}
		}

		bool AddState(AE_UINT id, std::shared_ptr<State> state)
		{
			if (StateExists(id) == false && state != nullptr)
			{
				state->setID(id);
				states.insert({ id, state });
				return true;
			}
			return false;
		}

		void SetState(AE_UINT id, AE_BOOL initialize, AE_BOOL transitionIn)
		{
			if (StateExists(id))
			{
				if (states.at(current_state) != nullptr)
				{
					current_state = id;

					if (initialize)
					{
						states.at(current_state)->Init();
					}

					if (transitionIn)
					{
						states.at(current_state)->TransitionIn();
					}
				}
			}
		}

		std::shared_ptr<State> GetState(AE_UINT id)
		{
			if (StateExists(id))
			{
				return states.at(id);
			}
			else
			{
				return nullptr;
			}
		}

		std::shared_ptr<State> GetCurrentState()
		{
			return states.at(current_state);
		}

		void RemoveState(AE_UINT id)
		{
			if (StateExists(id))
			{
				states.erase(id);
			}
		}

		bool StateExists(AE_UINT id)
		{
			return states.count(id);
		}

	};

};