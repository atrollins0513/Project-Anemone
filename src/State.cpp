#include "..\Anemone\State.h"

namespace Anemone
{

	namespace StateManager
	{

		namespace
		{
			unsigned int current_state = 0;
			std::unordered_map<unsigned int, std::shared_ptr<State>> states;
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

		void Update(double dt)
		{
			states.at(current_state)->Update(dt);
		}

		void Render(double alpha)
		{
			states.at(current_state)->Render(alpha);
		}

		void KeyEvent(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			states.at(current_state)->KeyEvent(window, key, scancode, action, mods);
		}

		void CharEvent(GLFWwindow * window, unsigned int codepoint)
		{
			states.at(current_state)->CharEvent(window, codepoint);
		}

		void MouseMoveEvent(GLFWwindow * window, double xpos, double ypos)
		{
			states.at(current_state)->MouseMoveEvent(window, xpos, ypos);
		}

		void MouseClickEvent(GLFWwindow * window, int button, int action, int mods)
		{
			states.at(current_state)->MouseClickEvent(window, button, action, mods);
		}

		void ScrollEvent(GLFWwindow * window, double xoffset, double yoffset)
		{
			states.at(current_state)->ScrollEvent(window, xoffset, yoffset);
		}

		void MouseEnterEvent(GLFWwindow * window, int entered)
		{
			states.at(current_state)->MouseEnterEvent(window, entered);
		}

		void JoystickEvent(int joy, int ev)
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

		bool AddState(unsigned int id, std::shared_ptr<State> state)
		{
			if (StateExists(id) == false && state != nullptr)
			{
				state->setID(id);
				states.insert({ id, state });
				return true;
			}
			return false;
		}

		void SetState(unsigned int id, bool initialize, bool transitionIn)
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

		std::shared_ptr<State> GetState(unsigned int id)
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

		void RemoveState(unsigned int id)
		{
			if (StateExists(id))
			{
				states.erase(id);
			}
		}

		bool StateExists(unsigned int id)
		{
			return (states.find(id) != states.end());
		}

	};

};