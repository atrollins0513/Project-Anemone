#include "..\Anemone\Window.h"

namespace ae
{
	bool Window::Create(const std::string& _title, unsigned int _width, unsigned int _height)// , sptr<State> initial_state)
	{
		glfwSetErrorCallback([](int error, const char* description) { log("Window", description); });
		toss(!glfwInit(), "Failed to initialize GLFW.");

		width = _width;
		height = _height;
		title = _title;
		setSeed((int)time(NULL));

		window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
		if (window == NULL)
		{
			toss(true, "Failed to open GLFW window.");
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);
		glewExperimental = true;
		toss(glewInit() != GLEW_OK, "Failed to initialize GLFW.");

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, width, height);
		glfwSetWindowUserPointer(window, this);

		glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {

			auto state = ((Window*)glfwGetWindowUserPointer(w))->getCurrentState();

			switch (action)
			{
				case GLFW_PRESS:
				{
					state->event(KeyPressedEvent(key, scancode, mods, 0));
					break;
				}
				case GLFW_RELEASE:
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
			auto state = ((Window*)glfwGetWindowUserPointer(w));
			ae::Input::setMousePos(ae::vec2((float)xpos, (float)(state->getHeight() - ypos)));
			state->getCurrentState()->event(MouseMoveEvent(xpos, ypos));
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
			((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->event(WindowFocusEvent(entered));
		});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* w, int width, int height) {
			((Window*)glfwGetWindowUserPointer(w))->getCurrentState()->event(WindowResizeEvent(width, height));
		});

		initialization();

		return true;
	}

	void Window::Start()
	{
		assert(current_state != nullptr, "State has not been set.");

		if (!window)
		{
			ae::log("Window", "The window's Create method has to be called before Start.");
			return;
		}

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
				update(dt);
				current_state->update(dt);
				accumulator -= dt;
			}

			current_state->render(accumulator / dt);
			render();

			glfwSwapBuffers(window);
		}
		glfwDestroyWindow(window);
	}

	void Window::setWindowTitle(const std::string& new_title)
	{
		toss(!window, "Window title cannot be set because the window has not been initialized.");
		title = new_title;
		glfwSetWindowTitle(window, title.c_str());
	}

	void Window::setUpdateRate(double _dt)
	{
		dt = _dt;
	}

	void Window::setScreenRefreshRate(unsigned int hertz)
	{
		monitorRefresh = hertz;
	}

	void Window::setPosition(int x, int y)
	{
		toss(!window, "Window position cannot be set because the window has not been initialized.");
		glfwSetWindowPos(window, x, y);
	}

	void Window::setWindowSize(unsigned int _width, unsigned int _height)
	{
		toss(!window, "Window size cannot be set because the window has not been initialized.");

		width = _width;
		height = _height;
		glfwSetWindowSize(window, width, height);
		glViewport(0, 0, width, height);
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

	void Window::enableFullScreen(bool windowed)
	{
		toss(!window, "Fullscreen cannot be enabled because the window has not been initialized.");

		fullscreen = true;
		monitor = glfwGetPrimaryMonitor();
		if (windowed)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			setHint(GLFW_RED_BITS, mode->redBits);
			setHint(GLFW_GREEN_BITS, mode->greenBits);
			setHint(GLFW_BLUE_BITS, mode->blueBits);
			setHint(GLFW_REFRESH_RATE, mode->refreshRate);
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else
		{
			glfwSetWindowMonitor(window, monitor, 0, 0, width, height, GL_DONT_CARE);
		}
	}

	void Window::disableFullScreen()
	{
		toss(!window, "Fullscreen cannot be disabled because the window has not been initialized.");

		fullscreen = false;
		int monitorX, monitorY, windowWidth, windowHeight;
		glfwGetMonitorPos(monitor, &monitorX, &monitorY);
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glfwSetWindowMonitor(window, nullptr, monitorX + (width - windowWidth) / 2, monitorY + (height - windowHeight) / 2, width, height, GLFW_DONT_CARE);
	}

	void Window::centerWindow()
	{
		toss(!window, "Window cannot be centered because the window has not been initialized.");

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		if (!mode) { return; }

		int monitorX, monitorY;
		glfwGetMonitorPos(glfwGetPrimaryMonitor(), &monitorX, &monitorY);
		setPosition(monitorX + (mode->width - width) / 2, monitorY + (mode->height - height) / 2);
	}

	void Window::setBorderlessWindow(bool borderless)
	{
		setHint(GLFW_DECORATED, !borderless);
	}

	void Window::useVSync(bool on)
	{
		glfwSwapInterval(on);
	}

	const std::unordered_map<unsigned int, std::vector<std::tuple<int, int, int>>> Window::getVideoModes() const
	{
		std::unordered_map<unsigned int, std::vector<std::tuple<int, int, int>>> videoModes;

		int monitorCount, modeCount;
		auto monitors = glfwGetMonitors(&monitorCount);

		for (auto m = 0; m < monitorCount; ++m)
		{
			auto modes = glfwGetVideoModes(monitors[m], &modeCount);

			std::vector<std::tuple<int, int, int>> modeStore;
			
			for (auto i = 0; i <= modeCount; i++)
			{

				if (modes[i].width > 0 && modes[i].height > 0 && modes[i].refreshRate > 0)
				{
					modeStore.push_back(std::make_tuple(modes[i].width, modes[i].height, modes[i].refreshRate));
				}

			}

			videoModes.emplace(m, modeStore);

		}

		return videoModes;
	}
};