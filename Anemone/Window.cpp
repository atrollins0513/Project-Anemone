#include "Window.h"

namespace Anemone
{
	Window::Window()
	{
		glfwSetErrorCallback([](AE_INT error, const AE_CHAR* description) {
			AE_CHAR log_buffer[8192];
			printf(log_buffer, "%s%s", "Error: ", description);
			Error::Log("Window", log_buffer);
		});

		if (!glfwInit())
		{
			Error::Log("Window", "Failed to initialize GLFW");
		}
	}

	bool Window::Create(const AE_CHAR* _title, AE_INT _width, AE_INT _height, GLFWmonitor* _monitor, GLFWwindow* _share, std::shared_ptr<State> initial_state)
	{
		w = _width;
		h = _height;
		monitor = _monitor;
		share = _share;
		title = _title;

		window = glfwCreateWindow(w, h, title, monitor, share);
		if (window == NULL)
		{
			Error::Log("Window", "Failed to open GLFW window.");
			glfwTerminate();
			return 0;
		}

		glfwMakeContextCurrent(window);
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			Error::Log("Window", "Failed to initialize GLEW");
			return 0;
		}

		StateManager::AddState(0, initial_state);
		StateManager::SetState(0, false);

		dt = 0.01;

		return true;
	}

	void Window::Start()
	{
		// Loop variables
		std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
		double accumulator = 0.0;
		std::chrono::high_resolution_clock::time_point newTime;
		double frameTime = 0.0;

		while (true)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			newTime = std::chrono::high_resolution_clock::now();
			frameTime = std::chrono::duration<double>(newTime - currentTime).count();
			if (frameTime > 0.25)
				frameTime = 0.25;
			currentTime = newTime;

			accumulator += frameTime;

			while (accumulator >= dt)
			{
				Anemone::StateManager::Update(dt);
				accumulator -= dt;
			}

			Anemone::StateManager::Render(accumulator / dt);

			// Swap buffers
			glfwSwapBuffers(window);
			glfwPollEvents();

			if (glfwWindowShouldClose(window) == GLFW_TRUE)
				break;
		}
		glfwDestroyWindow(window);
	}

	void Window::enableEvent(AE_UINT e)
	{
		if (e & KEYBOARD_EVENT)
		{
			glfwSetKeyCallback(window, StateManager::KeyEvent);
		}
		if (e & TEXT_EVENT)
		{
			glfwSetCharCallback(window, StateManager::CharEvent);
		}
		if (e & MOUSE_MOUSE_EVENT)
		{
			glfwSetCursorPosCallback(window, StateManager::MouseMoveEvent);
		}
		if (e & MOUSE_CLICK_EVENT)
		{
			glfwSetMouseButtonCallback(window, StateManager::MouseClickEvent);
		}
		if (e & MOUSE_SCROLL_EVENT)
		{
			glfwSetScrollCallback(window, StateManager::ScrollEvent);
		}
		if (e & MOUSE_CURSOR_ENTER_LEAVE_EVENT)
		{
			glfwSetCursorEnterCallback(window, StateManager::MouseEnterEvent);
		}
		if (e & JOYSTICK_EVENT)
		{
			glfwSetJoystickCallback(StateManager::JoystickEvent);
		}
	}
};