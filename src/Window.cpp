#include "..\Anemone\Window.h"

namespace Anemone
{
	Window::Window()
	{
		w = 1280;
		h = 720;
		monitor = nullptr;
		share = nullptr;
		title = "";
		dt = 0.01;
		window = nullptr;

		glfwSetErrorCallback([](int error, const char* description) {
			char log_buffer[8192];
			printf(log_buffer, "%s%s", "Error: ", description);
			Error::Log("Window", log_buffer);
		});

		if (!glfwInit())
		{
			Error::Log("Window", "Failed to initialize GLFW");
		}
	}

	bool Window::Create(std::string _title, unsigned int _width, unsigned int _height, GLFWmonitor* _monitor, GLFWwindow* _share)
	{
		w = _width;
		h = _height;
		monitor = _monitor;
		share = _share;
		title = _title;

		window = glfwCreateWindow(w, h, title.c_str(), monitor, share);
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

		dt = 0.01;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0.0f, 0.0f, w, h);

		return true;
	}

	void Window::Start()
	{
		if (window != nullptr)
		{
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

				glfwPollEvents();

				while (accumulator >= dt)
				{
					Anemone::StateManager::Update(dt);
					accumulator -= dt;
				}

				Anemone::StateManager::Render(accumulator / dt);

				glfwSwapBuffers(window);

				if (glfwWindowShouldClose(window) == GLFW_TRUE)
					break;
			}
			glfwDestroyWindow(window);
		}
	}

	void Window::enableEvent(unsigned int e)
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

	void Window::setWindowTitle(std::string new_title)
	{
		title = new_title;
		glfwSetWindowTitle(window, new_title.c_str());
	}

	void Window::setUpdateRate(double _dt)
	{
		dt = _dt;
	}

	void Window::setWindowPosition(int x, int y)
	{
		glfwSetWindowPos(window, x, y);
	}

	void Window::setHint(int hint, int value)
	{
		glfwWindowHint(hint, value);
	}

	std::shared_ptr<Anemone::Window> MakeWindow()
	{
		return std::make_shared<Anemone::Window>();
	}
};