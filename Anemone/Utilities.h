#pragma once

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <chrono>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <exception>

#include "Error.h"
#include "Base.h"
#include "Math.h"
#include "utilities/QuadTree.h"
#include "utilities/Noise.h"
#include "utilities/Pathfinding.h"
#include "utilities/ECS.h"
#include "utilities/Animation.h"

#define CANNOT_ALLOW(condition, why) assert((why, condition));

namespace ae
{
	// Pointer Utilities

	template<typename T>
	using sptr = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr sptr<T> makes(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using uptr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr uptr<T> makeu(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	// File Utilities

	extern std::string loadFile(const std::string& filename, int file_mode = std::ios::in);

	// String Utilities

	extern std::vector<std::string> explode(const std::string& s, char delim);

	// Timer

	struct timer
	{
	public:
		static void start();
		static void stop();
		static long long nano();
		static long long micro();
		static long long milli();
		static void basic(std::function<void()> func);
		static void basic(const std::string& log_msg, std::function<void()> func);
	private:
		static std::chrono::steady_clock::time_point begin;
		static std::chrono::steady_clock::time_point end;
	};

	// FPS Counter

	struct fps
	{
	public:
		static bool update(double dt);
		static const unsigned int get();
		static void tick();
	private:
		static double timer;
		static unsigned int count;
		static unsigned int last_fps;
	};

	// Event Queue

	class EventQueue : public Base
	{
	public:

		void update(double dt);

		void addEvent(double delay, double duration, bool repeat, std::function<bool()> callback);

	private:

		struct EventQueueEvent
		{
			double timer		{ 0.0 };
			double delay		{ 0.0 };
			double duration		{ 0.0 };
			bool repeat			{ false };
			std::function<bool()> callback;
		};

		std::vector<EventQueueEvent> events;

	};

	// Task Manager

	using FuncPtr = std::function<void(void)>;

	class TaskManager
	{
	public:

		TaskManager(unsigned int thread_count);

		void addTask(FuncPtr func);

		void dispatchThread();

		~TaskManager();

	private:

		bool quit	{ false };
		std::mutex lock;
		std::condition_variable cv;
		std::vector<std::thread> threads;
		std::queue<FuncPtr> tasks;

	};

};