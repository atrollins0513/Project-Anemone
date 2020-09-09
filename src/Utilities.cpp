#include "..\Anemone\Utilities.h"

namespace ae
{

	// Error Utilities

	void log(const std::string& identifier, const std::string& message)
	{
		std::ofstream file("log.txt", std::ios::out);
		if (file.is_open())
		{
			time_t rawtime;
			struct tm* timeinfo;
			char buffer[25];
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			strftime(buffer, 25, "[%F %H:%M:%S]", timeinfo);
			file << buffer << "[" << identifier << "]" << "[" << message << "]" << std::endl;
			file.close();
		}
	}

	void log(const std::string& identifier, const std::string& message, const std::string& message_two)
	{
		std::ofstream file("log.txt", std::ios::out);
		if (file.is_open())
		{
			time_t rawtime;
			struct tm* timeinfo;
			char buffer[25];
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			strftime(buffer, 25, "[%F %H:%M:%S]", timeinfo);
			file << buffer << "[" << identifier << "]" << "[" << message << message_two << "]" << std::endl;
			file.close();
		}
	}

	void toss(bool trigger, const std::string& msg)
	{
		if (trigger) { throw msg; }
	}

	// File Utilities

	std::string loadFile(const std::string& filename, int file_mode)
	{
		std::ifstream file(filename, file_mode);

		std::string data;

		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			unsigned long size = (unsigned long)file.tellg();
			file.seekg(0, std::ios::beg);

			if (size <= 0)
			{
				file.close();
				return "";
			}

			char* fileData = new char[size + 1];
			file.read((char*)fileData, size);

			data = fileData;

			delete[] fileData;

			file.close();

			return data;
		}
		else
		{
			log(filename, "Failed to open.");
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

	void setSeed(int seed)
	{
		srand(seed);
	}

	// Random Function Utilities

	int random(unsigned int upper_limit)
	{
		return rand() % upper_limit;
	}

	int random(unsigned int lower_limit, unsigned int upper_limit)
	{
		return (rand() % (upper_limit - lower_limit)) + lower_limit;
	}

	vec2 randVec2(unsigned int min, unsigned int max)
	{
		return vec2((float)random(min, max), (float)random(min, max));
	}

	vec3 randVec3(unsigned int min, unsigned int max)
	{
		return vec3((float)random(min, max), (float)random(min, max), (float)random(min, max));
	}

	vec4 randVec4(unsigned int min, unsigned int max)
	{
		return vec4((float)random(min, max), (float)random(min, max), (float)random(min, max), (float)random(min, max));
	}

	// Timer

	namespace timer
	{

		namespace
		{
			std::chrono::steady_clock::time_point clock_start = std::chrono::high_resolution_clock::now();
			std::chrono::steady_clock::time_point clock_end = std::chrono::high_resolution_clock::now();
		}

		void begin()
		{
			clock_start = std::chrono::high_resolution_clock::now();
		}

		void stop()
		{
			clock_end = std::chrono::high_resolution_clock::now();
		}

		long long getNanoSeconds()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end - clock_start).count();
		}

		long long getMicroSeconds()
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(clock_end - clock_start).count();
		}

		long long getMilliSeconds()
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(clock_end - clock_start).count();
		}

		void basic(std::function<void()> func)
		{
			std::chrono::steady_clock::time_point start, end;
			start = std::chrono::high_resolution_clock::now();
			func();
			end = std::chrono::high_resolution_clock::now();
			auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
			std::cout << "[" << t << " ns]\t[";
			std::cout << t / 1000.0 << " mus]\t[";
			std::cout << t / 1000.0 / 1000.0 << " ms]\n";
		}

		void basic(const std::string& log_msg, std::function<void()> func)
		{
			std::cout << log_msg << "\n\t";
			basic(func);
		}

	};

	// FPS Counter

	bool FPSCounter::update(double dt)
	{
		fps_timer += dt;
		if (fps_timer >= 1.0)
		{
			fps_timer = 0;
			last_fps = fps;
			fps = 0;
			return true;
		}
		return false;
	}

	const unsigned int FPSCounter::get() const
	{
		return last_fps;
	}

	void FPSCounter::operator++()
	{
		fps++;
	}

	void FPSCounter::operator++(int unused)
	{
		fps++;
	}

	// Event Queue

	void EventQueue::update(double dt)
	{
		for (auto it = events.begin(); it != events.end();)
		{
			auto& e = (*it);

			if ((e.timer += dt) >= e.delay + e.duration)
			{
				e.callback();
				if (e.repeat)
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

	void EventQueue::addEvent(double delay, double duration, bool repeat, std::function<void()> callback)
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

	TaskManager::TaskManager(unsigned int thread_count) : threads(thread_count)
	{
		for (unsigned int i = 0; i < thread_count; i++)
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