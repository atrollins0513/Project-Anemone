#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include "Anemone.h"

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <memory>
#include <string>

#define GLEW_STATIC
#include "includes\glew.h"
#include "includes\glfw3.h"

#include "State.h"
#include "Error.h"

namespace Anemone
{
	enum INPUT_EVENT { KEYBOARD_EVENT = 0x01, TEXT_EVENT = 0x02, MOUSE_MOUSE_EVENT = 0x04, MOUSE_CLICK_EVENT = 0x08, MOUSE_SCROLL_EVENT = 0x16, MOUSE_CURSOR_ENTER_LEAVE_EVENT = 0x32, JOYSTICK_EVENT = 0x64};

	class State;

	class Window
	{
	public:

		Window();
		
		bool Create(std::string _title, AE_UINT _width, AE_UINT _height, GLFWmonitor* _monitor = nullptr, GLFWwindow* _share = nullptr);
		
		void Start();

		void enableEvent(AE_UINT e);

		void setWindowTitle(std::string new_title);

		void setUpdateRate(double _dt);

		GLFWwindow* handle() { return window; }

		const AE_INT width() { return w; }

		const AE_INT height() { return h; }

		const AE_DOUBLE getUpdateRate() { return dt; }

	protected:
	private:

		AE_UINT w;

		AE_UINT h;

		std::string title;

		GLFWmonitor* monitor;

		GLFWwindow* share;

		GLFWwindow* window;

		AE_DOUBLE dt;

	};

	extern std::shared_ptr<Anemone::Window> MakeWindow();
};