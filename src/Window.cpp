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
		current_state = nullptr;
		setStateManagerParent(this);

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

	bool Window::Create(const std::string& _title, unsigned int _width, unsigned int _height, sptr<State> initial_state)
	{
		w = _width;
		h = _height;
		title = _title;
		dt = 0.01;

		window = glfwCreateWindow(w, h, title.c_str(), monitor, share);
		if (window == NULL)
		{
			log("Window", "Failed to open GLFW window.");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			log("Window", "Failed to initialize GLEW");
			return false;
		}

		addState(initial_state);
		setState(initial_state->getName(), true);

		glfwSetWindowUserPointer(window, this);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, w, h);

		glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {

			auto state = ((Window*)glfwGetWindowUserPointer(w))->getCurrentState();

			switch (action)
			{
				case GLFW_KEY_DOWN:
				{
					state->event(KeyPressedEvent(key, scancode, mods, 0));
					break;
				}
				case GLFW_KEY_UP:
				{
					state->event(KeyReleasedEvent(key, scancode, mods));
					break;
				}
				case GLFW_REPEAT:
				{
					state->event(KeyPressedEvent(key, scancode, mods, 1));
					break;
				}
			}
		});

		glfwSetCharCallback(window, [](GLFWwindow* w, unsigned int codepoint) {
			((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->event(KeyTypedEvent(codepoint));
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* w, double xpos, double ypos) {
			((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->event(MouseMoveEvent(xpos, ypos));
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods) {
			auto state = ((Window*)glfwGetWindowUserPointer(w))->getCurrentState();

			switch (action)
			{
				case GLFW_PRESS:
				{
					state->event(MouseDownEvent(button, mods));
					break;
				}
				case GLFW_RELEASE:
				{
					state->event(MouseReleaseEvent(button, mods));
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* w, double xoffset, double yoffset) {
			((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->event(MouseScrollEvent(xoffset, yoffset));
		});

		glfwSetCursorEnterCallback(window, [](GLFWwindow* w, int entered) {
			((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->event(WindowFocus(entered));
		});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* w, int width, int height) {
			((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->event(WindowResizeEvent(width, height));
		});

		return true;
	}

	void Window::Start()
	{
		assert(current_state != nullptr);

		if (window != nullptr)
		{
			std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
			double accumulator = 0.0;
			std::chrono::high_resolution_clock::time_point newTime;
			double frameTime = 0.0;

			while (!glfwWindowShouldClose(window))
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
					//sm->getCurrentState()->update(dt);
					current_state->update(dt);
					accumulator -= dt;
				}

				//sm->getCurrentState()->render(accumulator / dt);
				current_state->render(accumulator / dt);

				glfwSwapBuffers(window);
			}
			glfwDestroyWindow(window);
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

	void Window::setMonitor(GLFWmonitor* _monitor)
	{
		monitor = _monitor;
	}

	void Window::setShare(GLFWwindow* _share)
	{
		share = _share;
	}

	sptr<Window> MakeWindow()
	{
		return makeShared<Window>();
	}
};