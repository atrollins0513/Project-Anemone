#pragma once

#include "Anemone.h"

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <memory>

#include <gl\glew.h>
#include <gl\glfw3.h>

#include "StateManager.h"
#include "Error.h"

namespace Anemone
{
	enum INPUT_EVENT { KEYBOARD_EVENT = 0x01, TEXT_EVENT = 0x02, MOUSE_MOUSE_EVENT = 0x04, MOUSE_CLICK_EVENT = 0x08, MOUSE_SCROLL_EVENT = 0x16, MOUSE_CURSOR_ENTER_LEAVE_EVENT = 0x32, JOYSTICK_EVENT = 0x64};

	class State;

	class Window
	{
	public:

		Window();
		
		bool Create(const AE_CHAR* _title, AE_INT _width, AE_INT _height, GLFWmonitor* _monitor, GLFWwindow* _share, std::shared_ptr<Anemone::State> initial_state);
		
		void Start();

		void enableEvent(AE_UINT e);

		GLFWwindow* handle()
		{
			return window;
		}

		AE_INT width() const
		{
			return w;
		}

		AE_INT height() const
		{
			return h;
		}

	protected:
	private:

		AE_INT w;

		AE_INT h;

		const AE_CHAR* title;

		GLFWmonitor* monitor;

		GLFWwindow* share;

		GLFWwindow* window;

	};
};