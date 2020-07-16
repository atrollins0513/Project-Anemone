#include "..\Anemone\Window.h"

namespace ae
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
			log("Window", log_buffer);
		});

		if (!glfwInit())
		{
			log("Window", "Failed to initialize GLFW");
		}
	}

	bool Window::Create(const std::string& _title, unsigned int _width, unsigned int _height, GLFWmonitor* _monitor, GLFWwindow* _share)
	{
		w = _width;
		h = _height;
		monitor = _monitor;
		share = _share;
		title = _title;

		window = glfwCreateWindow(w, h, title.c_str(), monitor, share);
		if (window == NULL)
		{
			log("Window", "Failed to open GLFW window.");
			glfwTerminate();
			return 0;
		}

		glfwMakeContextCurrent(window);
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			log("Window", "Failed to initialize GLEW");
			return 0;
		}

		dt = 0.01;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, w, h);

		glfwSetWindowUserPointer(window, this);
		sm.parent = this;

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
					sm.getCurrentState()->update(dt);
					accumulator -= dt;
				}

				sm.getCurrentState()->render(accumulator / dt);

				glfwSwapBuffers(window);

				if (glfwWindowShouldClose(window) == GLFW_TRUE)
					break;
			}
			glfwDestroyWindow(window);
		}
	}

	void Window::enableEvent(Event e)
	{
		if (e & Event::KEYBOARD_EVENT)
		{
			//glfwSetKeyCallback(window, StateManager::KeyEvent);
			glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {
				((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->keyEvent(key, scancode, action, mods);
			});
		}

		if (e & TEXT_EVENT)
		{
			glfwSetCharCallback(window, [](GLFWwindow* w, unsigned int codepoint) {
				((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->charEvent(codepoint);
			});
		}

		if (e & MOUSE_MOUSE_EVENT)
		{
			glfwSetCursorPosCallback(window, [](GLFWwindow* w, double xpos, double ypos) {
				((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->mouseMoveEvent(xpos, ypos);
			});
		}

		if (e & MOUSE_CLICK_EVENT)
		{
			glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods) {
				((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->mouseClickEvent(button, action, mods);
			});
		}

		if (e & MOUSE_SCROLL_EVENT)
		{
			glfwSetScrollCallback(window, [](GLFWwindow* w, double xoffset, double yoffset) {
				((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->scrollEvent(xoffset, yoffset);
			});
		}

		if (e & MOUSE_CURSOR_ENTER_LEAVE_EVENT)
		{
			glfwSetCursorEnterCallback(window, [](GLFWwindow* w, int entered) {
				((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->mouseEnterEvent(entered);
			});
		}

		if (e & JOYSTICK_EVENT)
		{
			glfwSetJoystickCallback([](int joy, int ev) {
				((Window*)glfwGetWindowUserPointer(glfwGetCurrentContext()))->getCurrentState()->joystickEvent(joy, ev);
			});
		}
	}

	void Window::setWindowTitle(const std::string& new_title)
	{
		title = new_title;
		glfwSetWindowTitle(window, title.c_str());
	}

	void Window::setUpdateRate(double _dt)
	{
		dt = _dt;
	}

	void Window::setPosition(int x, int y)
	{
		glfwSetWindowPos(window, x, y);
	}

	void Window::setHint(int hint, int value)
	{
		glfwWindowHint(hint, value);
	}

	std::shared_ptr<Window> MakeWindow()
	{
		return std::make_shared<Window>();
	}
};