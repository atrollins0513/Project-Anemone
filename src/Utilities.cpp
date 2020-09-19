#include "..\Anemone\Utilities.h"

namespace ae
{

	// File Utilities

	std::string loadFile(const std::string& filename, int file_mode)
	{
		std::ifstream file(filename, std::ios::in);

		if (file.is_open())
		{
			std::string data;
			file.seekg(0, std::ios::end);
			data.resize(file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&data[0], data.size());
			file.close();
			return data;
		}
		else
		{
			log(filename, "Failed to open file.");
			return "";
		}
	}

	// String Utilities

	std::vector<std::string> explode(const std::string& s, char delim)
	{
		std::vector<std::string> result;
		std::istringstream iss(s);

		for (std::string token; std::getline(iss, token, delim); )
		{
			result.push_back(std::move(token));
		}

		return result;
	}

	// Timer

	std::chrono::steady_clock::time_point timer::begin	{ std::chrono::high_resolution_clock::now() };
	std::chrono::steady_clock::time_point timer::end	{ std::chrono::high_resolution_clock::now() };

	void timer::start()
	{
		begin = std::chrono::high_resolution_clock::now();
	}

	void timer::stop()
	{
		end = std::chrono::high_resolution_clock::now();
	}

	long long timer::nano()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
	}

	long long timer::micro()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	}

	long long timer::milli()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	}

	void timer::basic(std::function<void()> func)
	{
		auto tbegin = std::chrono::high_resolution_clock::now();
		func();
		auto tend = std::chrono::high_resolution_clock::now() - tbegin;
		auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(tend).count();
		std::cout << "[" << t << " ns]\t[";
		std::cout << t / 1000.0 << " mus]\t[";
		std::cout << t / 1000.0 / 1000.0 << " ms]\n";
	}

	void timer::basic(const std::string& log_msg, std::function<void()> func)
	{
		std::cout << log_msg << "\n\t";
		basic(func);
	}

	// FPS Counter

	double fps::timer = 0.0;
	unsigned int fps::count = 0;
	unsigned int fps::last_fps = 0;

	bool fps::update(double dt)
	{
		timer += dt;
		if (timer >= 1.0)
		{
			timer = 0;
			last_fps = count;
			count = 0;
			return true;
		}
		return false;
	}

	const unsigned int fps::get()
	{
		return last_fps;
	}

	void fps::tick()
	{
		count++;
	}

	// Event Queue

	void EventQueue::update(double dt)
	{
		for (auto it = events.begin(); it != events.end();)
		{
			auto& e = (*it);

			if ((e.timer += dt) >= e.delay + e.duration)
			{
				bool remove = e.callback();
				if (e.repeat && !remove)
				{
					e.timer = e.delay;
					++it;
				}
				else
				{
					it = events.erase(it);
				}
			}
			else
			{
				++it;
			}
		}
	}

	void EventQueue::addEvent(double delay, double duration, bool repeat, std::function<bool()> callback)
	{
		EventQueueEvent e;
		e.timer = 0.0;
		e.delay = delay;
		e.duration = duration;
		e.repeat = repeat;
		e.callback = callback;
		events.push_back(e);
	}

	// Task Manager

	TaskManager::TaskManager(unsigned int thread_count)
	{
		for (unsigned int i = 0; i < thread_count; ++i)
		{
			threads.push_back(std::thread(&TaskManager::dispatchThread, this));
		}

		quit = false;
	}

	void TaskManager::addTask(FuncPtr func)
	{
		std::unique_lock<std::mutex> l(lock);
		tasks.push(func);
		l.unlock();
		cv.notify_one();
	}

	void TaskManager::dispatchThread()
	{
		std::unique_lock<std::mutex> l(lock);

		while (!quit)
		{
			cv.wait(l, [this] { return (tasks.size() || quit); });

			if (tasks.size())
			{
				auto func = std::move(tasks.front());

				tasks.pop();

				l.unlock();

				func();

				l.lock();
			}
		}
	}

	TaskManager::~TaskManager()
	{
		quit = true;

		cv.notify_all();

		for (unsigned int i = 0; i < threads.size(); i++)
		{
			if (threads[i].joinable())
			{
				threads[i].join();
			}
		}
	}

};