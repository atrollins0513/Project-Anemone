#pragma once

#include "Anemone.h"

#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#include <gl\glew.h>
#include <gl\glfw3.h>

#include "StateManager.h"
#include "Error.h"

namespace Anemone
{
	class Window
	{
	public:

		Window();
		
		bool Create(const AE_CHAR* _title, AE_INT _width, AE_INT _height, GLFWmonitor* _monitor, GLFWwindow* _share);
		
		void Start();

		GLFWwindow* handle()
		{
			return window;
		}

	protected:
	private:

		AE_INT width;

		AE_INT height;

		const AE_CHAR* title;

		GLFWmonitor* monitor;

		GLFWwindow* share;

		GLFWwindow* window;

	};
};