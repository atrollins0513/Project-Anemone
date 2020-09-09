#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>
#include <tuple>

#include "includes\glew.h"
#include "includes\glfw3.h"

#include "Utilities.h"
#include "Event.h"
#include "State.h"

namespace ae
{
	class State;

	class Window : public StateManager
	{
	public:

		bool Create(const std::string& _title, unsigned int _width, unsigned int _height);
		
		virtual void Start();

		void setWindowTitle(const std::string& new_title);

		void setUpdateRate(double _dt);

		void setScreenRefreshRate(unsigned int hertz);

		void setPosition(int x, int y);

		void setWindowSize(unsigned int _width, unsigned int _height);

		void setHint(int hint, int value);

		GLFWwindow* handle() { return window; }
	
		void setMonitor(GLFWmonitor* _monitor);

		void setShare(GLFWwindow* _share);

		const unsigned int getWidth() const { return width; }

		const unsigned int getHeight() const { return height; }

		const vec2 getCenter() const { return vec2((float)width, (float)height) / 2.0f; }

		const double getUpdateRate() { return dt; }

		void enableFullScreen(bool windowed = false);

		void disableFullScreen();

		void centerWindow();

		void setBorderlessWindow(bool borderless);

		void useVSync(bool on);

		const std::unordered_map<unsigned int, std::vector<std::tuple<int, int, int>>> getVideoModes() const;

	protected:

		virtual void initialization() {};

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