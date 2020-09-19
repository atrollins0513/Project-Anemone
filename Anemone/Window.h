#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>
#include <tuple>
#include <fstream>

#include "includes\gl3w.h"
#include "includes\glfw3.h"

#include "Error.h"
#include "Utilities.h"
#include "Event.h"
#include "State.h"

namespace ae
{
	class State;

	class Window : public StateManager
	{
	public:

		enum Hints
		{
			BORDERLESS = 0x01,
			FULLSCREEN = 0x02
		};

		Window() = default;

		Window(const std::string& _title, unsigned int _width, unsigned int _height);

		void create(const std::string& _title, unsigned int _width, unsigned int _height, unsigned int hints = 0);
		
		virtual void start();

		void setWindowTitle(const std::string& new_title);

		void setUpdateRate(double _dt);

		void setScreenRefreshRate(unsigned int hertz);

		void setPosition(int x, int y);

		void setWindowSize(unsigned int _width, unsigned int _height);

		void setHint(int hint, int value);

		void setMonitor(GLFWmonitor* _monitor);

		void setShare(GLFWwindow* _share);

		void setBorderlessWindow(bool borderless);

		void useVSync(bool on);

		GLFWwindow* handle() { return window; }
	
		const unsigned int getWidth() const { return width; }

		const unsigned int getHeight() const { return height; }

		const vec2 getCenter() const { return vec2((float)width, (float)height) / 2.0f; }

		const double getUpdateRate() { return dt; }

		void enableFullScreen(bool windowed = false);

		void disableFullScreen();

		void centerWindow();

		const std::unordered_map<unsigned int, std::vector<std::tuple<int, int, int>>> getVideoModes() const;

	protected:

		virtual void update(double dt) {};
		virtual void render() {};

		std::string title			{ "" };
		unsigned int width			{ 1280 };
		unsigned int height			{ 720 };
		GLFWmonitor* monitor		{ nullptr };
		GLFWwindow* share			{ nullptr };
		GLFWwindow* window			{ nullptr };
		bool fullscreen				{ false };
		double dt					{ 0.01 };
		unsigned int monitorRefresh	{ 60 };
		std::unordered_map<unsigned int, std::tuple<int, int, int>> videoModes;

	};
};