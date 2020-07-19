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
#include "Event.h"

namespace ae
{
	class State;

	class Window : public StateManager
	{
	public:

		Window();
		
		bool Create(const std::string& _title, unsigned int _width, unsigned int _height, sptr<State> initial_state);
		
		void Start();

		void setWindowTitle(const std::string& new_title);

		void setUpdateRate(double _dt);

		void setPosition(int x, int y);

		void setHint(int hint, int value);

		GLFWwindow* handle() { return window; }
	
		void setMonitor(GLFWmonitor* _monitor);

		void setShare(GLFWwindow* _share);

		const unsigned int getWidth() { return width; }

		const unsigned int getHeight() { return height; }

		const double getUpdateRate() { return dt; }


		//sptr<StateManager> getStateManager() { return sm; }

		//const sptr<State> getCurrentState() { return sm->getCurrentState(); };

	protected:
	private:

		unsigned int width;

		unsigned int height;

		std::string title;

		GLFWmonitor* monitor;

		GLFWwindow* share;

		GLFWwindow* window;

		double dt;

		//sptr<StateManager> sm;

	};

	extern sptr<Window> MakeWindow();
};