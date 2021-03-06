#include "..\Anemone\Window.h"

namespace ae
{

	Window::Window(const std::string& _title, unsigned int _width, unsigned int _height)
	{
		create(_title, _width, _height);
	}

	void Window::create(const std::string& _title, unsigned int _width, unsigned int _height, unsigned int hints)
	{
		width = _width;
		height = _height;
		title = _title;
		setSeed((int)time(NULL));

		std::ofstream log_file("log.txt");
		if (log_file.is_open()) {
			log_file.close();
		}

		// Initialize GLFW
		glfwSetErrorCallback([](int error, const char* description) { log("Window", description); });
		if (!glfwInit()) {
			log("Window", "Failed to initialize GLFW");
			return;
		}

		if (hints & Hints::BORDERLESS) {
			setHint(AE_DECORATED, AE_FALSE);
		}

		// If GLFW Initializes, then create the Window
		window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
		if (window == NULL) {
			log("Window", "Failed to open GLFW window.");
			glfwTerminate();
			return;
		}

		// Set GLFW to point to the current window
		glfwMakeContextCurrent(window);

		// Initialize GL3W
		if (gl3wInit())
		{
			log("Window", "Failed to initialize GL3W");
			glfwTerminate();
			return;
		}
		if (!gl3wIsSupported(3, 2))
		{
			log("Window", "System must support OpenGL version 3.2 or newer");
			glfwTerminate();
			return;
		}

		if (hints & Hints::FULLSCREEN) {
			enableFullScreen((hints & Hints::BORDERLESS));
		} else {
			if (hints & Hints::BORDERLESS) {
				centerWindow();
			}
		}

		// If every initializes properly, then setup some basic OpenGL stuff and set event callbacks
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
	}

	void Window::start()
	{
		toss(current_state == nullptr, "State has not been set.");
		toss(window == nullptr, "Window has to been created before you can start.");

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

	void Window::setBorderlessWindow(bool borderless)
	{
		setHint(GLFW_DECORATED, !borderless);
	}

	void Window::useVSync(bool on)
	{
		glfwSwapInterval(on);
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
			glfwSetWindowMonitor(window, monitor, 0, 0, width, height, GLFW_DONT_CARE);
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