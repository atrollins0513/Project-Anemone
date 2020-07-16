#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <memory>
#include <string>

#include "includes\glew.h"
#include "includes\glfw3.h"

#include "Utilities.h"
#include "State.h"

namespace ae
{
	enum Event { KEYBOARD_EVENT = 0x01, TEXT_EVENT = 0x02, MOUSE_MOUSE_EVENT = 0x04, MOUSE_CLICK_EVENT = 0x08, MOUSE_SCROLL_EVENT = 0x16, MOUSE_CURSOR_ENTER_LEAVE_EVENT = 0x32, JOYSTICK_EVENT = 0x64};

	class State;

	class Window
	{
	public:

		Window();
		
		bool Create(const std::string& _title, unsigned int _width, unsigned int _height, GLFWmonitor* _monitor = nullptr, GLFWwindow* _share = nullptr);
		
		void Start();

		void enableEvent(Event e);

		void setWindowTitle(const std::string& new_title);

		void setUpdateRate(double _dt);

		void setPosition(int x, int y);

		void setHint(int hint, int value);

		GLFWwindow* handle() { return window; }

		const int width() { return w; }

		const int height() { return h; }

		const double getUpdateRate() { return dt; }

		const StateManager& getStateManager() { return sm; }

		const std::shared_ptr<State> getCurrentState() { return sm.getCurrentState(); };

	protected:
	private:

		unsigned int w;

		unsigned int h;

		std::string title;

		GLFWmonitor* monitor;

		GLFWwindow* share;

		GLFWwindow* window;

		double dt;

		StateManager sm;

	};

	extern std::shared_ptr<Window> MakeWindow();
};