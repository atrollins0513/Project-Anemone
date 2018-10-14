#pragma once

#include "Anemone.h"

#include <memory>
#include <unordered_map>
#include <tuple>
#include "includes\glew.h"
#include "includes\glfw3.h"

#include "State.h"

namespace Anemone
{
	namespace StateManager
	{

		namespace
		{

			extern AE_UINT current_state;

			extern std::unordered_map<AE_UINT, std::shared_ptr<State>> states;

			extern std::unordered_map<AE_UINT, AE_BOOL> initialization_list;

		};

		extern void Init();

		extern void Update(AE_DOUBLE dt);

		extern void Render(AE_DOUBLE alpha);

		extern void KeyEvent(GLFWwindow* window, AE_INT key, AE_INT scancode, AE_INT action, AE_INT mods);

		extern void CharEvent(GLFWwindow* window, AE_UINT codepoint);

		extern void MouseMoveEvent(GLFWwindow* window, AE_DOUBLE xpos, AE_DOUBLE ypos);

		extern void MouseClickEvent(GLFWwindow* window, AE_INT button, AE_INT action, AE_INT mods);

		extern void ScrollEvent(GLFWwindow* window, AE_DOUBLE xoffset, AE_DOUBLE yoffset);

		extern void MouseEnterEvent(GLFWwindow* window, AE_INT entered);

		extern void JoystickEvent(AE_INT joy, AE_INT ev);


		extern void Destroy();


		extern void AddState(AE_UINT id, std::shared_ptr<State> state);

		extern void SetState(AE_UINT id, AE_BOOL transition_in = false);

		extern std::shared_ptr<State> GetState(AE_UINT id);

		extern std::shared_ptr<State> GetCurrentState();

		extern void RemoveState(AE_UINT id);

	};
};