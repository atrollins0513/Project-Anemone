#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <random>
#include <time.h>
#include <memory>
#include <chrono>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>

#include "Math.h"

#include "utilities/QuadTree.h"
#include "utilities/Noise.h"
#include "utilities/Pathfinding.h"
#include "utilities/ECS.h"
#include "utilities/Animation.h"

namespace ae
{

	// Pointer Utilities

	template<typename T>
	using sptr = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr sptr<T> makeShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using uptr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr uptr<T> makeUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	struct MakeSmartExt
	{
		template<typename ... Args>
		static ae::sptr<T> Create(Args&& ... args)
		{
			return ae::makeShared<T>(std::forward<Args>(args)...);
		}

		template<typename ... Args>
		static ae::uptr<T> CreateU(Args&& ... args)
		{
			return ae::makeUnique<T>(std::forward<Args>(args)...);
		}
	};

	// Error Utilities

	extern void log(const std::string& identifier, const std::string& message);

	extern void log(const std::string& identifier, const std::string& message, const std::string& message_two);

	// File Utilities

	extern std::string loadFile(const std::string& filename, int file_mode = std::ios::in);

	// String Utilities

	extern std::vector<std::string> explode(const std::string& s, char delim);

	// Random Function Utilities

	extern void setSeed(int seed);

	extern int random(unsigned int upper_limit);

	extern int random(unsigned int lower_limit, unsigned int upper_limit);

	extern vec2 randVec2(unsigned int min = 0, unsigned int max = 255);

	extern vec3 randVec3(unsigned int min = 0, unsigned int max = 255);

	extern vec4 randVec4(unsigned int min = 0, unsigned int max = 255);

	// Color Utilities

	constexpr vec3 hexToRGB(int hex)
	{
		return vec3(((hex >> 16) & 0xFF) / 255.0f, ((hex >> 8) & 0xFF) / 255.0f, (hex & 0xFF) / 255.0f);
	}

	// Timer

	namespace timer
	{

		namespace
		{
			extern std::chrono::steady_clock::time_point clock_start;
			extern std::chrono::steady_clock::time_point clock_end;
		}

		extern void begin();

		extern void stop();

		extern long long getNanoSeconds();

		extern long long getMicroSeconds();

		extern long long getMilliSeconds();

		extern void basic(std::function<void()> func);

		extern void basic(const std::string& log_msg, std::function<void()> func);

	};

	// FPS Counter

	class FPSCounter
	{
	public:

		FPSCounter() : fps(0), last_fps(0), fps_timer(0.0) { }

		bool update(double dt);

		const unsigned int get() const;

		void operator++();

		void operator++(int unused);

	private:

		unsigned int fps;

		unsigned int last_fps;

		double fps_timer;

	};

	// Event Queue

	class EventQueue
	{
	public:

		EventQueue() { }

		void update(double dt);

		void addEvent(double delay, double duration, bool repeat, std::function<void()> callback);

	private:

		struct EventQueueEvent
		{
			double timer;
			double delay;
			double duration;
			bool repeat;
			std::function<void()> callback;
		};

		std::vector<EventQueueEvent> events;

	};

	// Tweening

	enum class EasingType { LINEAR, SINE, QUAD, CUBIC, QUART, QUINT, EXP, CIR, BACK, ELASTIC, BOUNCE };

	enum class EasingMode { EASE_IN = 0 , EASE_OUT, EASE_INOUT };

	template<typename T>
	class Tween
	{
	public:

		Tween() : pos(0), target(0), ease(0.0f), delta(0.0f), speed(0.001f), complete(true), epsilon(0.1), type(EasingType::SINE), mode(EasingMode::EASE_INOUT) { }

		Tween(T _pos, T _target, float _ease) : Tween(), pos(_pos), target(_target), ease(_ease) { }

		Tween& set(T _pos, T _target)
		{
			pos = _pos;
			target = _target;
			complete = false;
			return *this;
		}

		Tween& setTarget(T _target)
		{
			delta = 0.0f;
			complete = false;
			target = _target;
			return *this;
		}

		Tween& setEasing(EasingType _type, EasingMode _mode)
		{
			setEasingType(_type);
			setEasingMode(_mode);
			return *this;
		}

		Tween& setEasingType(EasingType _type)
		{
			type = _type;
			return *this;
		}

		Tween& setEasingMode(EasingMode _mode)
		{
			mode = _mode;
			return *this;
		}

		Tween& setSpeed(float _speed)
		{
			speed = 0.00001f * _speed;
			return *this;
		}

		Tween& setEpsilon(double _epsilon)
		{
			epsilon = _epsilon;
			return *this;
		}

		bool update(double dt)
		{
			if (complete == false)
			{
				pos += (type == EasingType::LINEAR ? ae::normalize((target - pos)) * speed * dt : (target - pos) * easingDelta((delta += speed * (float)dt)));

				T difference = target - pos;
				if ((difference < 0.0f ? difference * -1.0f : difference) > epsilon)
				{
					if (update_callback)
					{
						update_callback(pos);
					}
				}
				else
				{
					complete = true;
					pos = target;
					if (finished_callback)
					{
						finished_callback();
					}
				}
			}

			return complete;
		}

		bool isComplete()
		{
			return complete;
		}

		const T& getPos() const
		{
			return pos;
		}

		const T& getTarget() const
		{
			return target;
		}

		void setFinishedCallback(std::function<void()> _finished_callback)
		{
			finished_callback = _finished_callback;
		}

		void setUpdateCallback(std::function<void(T)> _update_callback)
		{
			update_callback = _update_callback;
		}

		void operator=(const Tween<T> other)
		{
			pos = other.pos;
			target = other.target;
			ease = other.ease;
			delta = other.delta;
			speed = other.speed;
			finished_callback = other.finished_callback;
			update_callback = other.update_callback;
			complete = other.complete;
			type = other.type;
			mode = other.mode;
			epsilon = other.epsilon;
		}

	private:

		float easingDelta(float x)
		{
			switch (type)
			{
			case EasingType::SINE:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return 1.0f - cos((x * PI) / 2.0f);
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return sin((x * PI) / 2.0f);
				}
				else
				{
					return -(cos(PI * x) - 1.0f) / 2.0f;
				}
				break;
			}
			case EasingType::QUAD:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return x * x;
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return 1.0f - (1.0f - x) * (1.0f - x);
				}
				else
				{
					return (x < 0.5f ? 2.0f * x * x : 1.0f - std::pow(-2.0f * x + 2.0f, 2.0f) / 2.0f);
				}
				break;
			}
			case EasingType::CUBIC:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return x * x * x;
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return 1.0f - std::pow(1.0f - x, 3.0f);
				}
				else
				{
					return (x < 0.5f ? 4.0f * x * x * x : 1.0f - std::pow(-2.0f * x + 2.0f, 3.0f) / 2.0f);
				}
				break;
			}
			case EasingType::QUART:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return x * x * x * x;
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return 1.0f - std::pow(1.0f - x, 4.0f);
				}
				else
				{
					return (x < 0.5f ? 8.0f * x * x * x * x : 1.0f - std::pow(-2.0f * x + 2.0f, 4.0f) / 2.0f);
				}
				break;
			}
			case EasingType::QUINT:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return x * x * x * x * x;
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return 1.0f - std::pow(1.0f - x, 5.0f);
				}
				else
				{
					return (x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - std::pow(-2.0f * x + 2.0f, 5.0f) / 2.0f);
				}
				break;
			}
			case EasingType::EXP:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return (x == 0.0f ? 0.0f : std::pow(2.0f, 10.0f * x - 10.0f));
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return (x == 1.0f ? 1.0f : 1.0f - std::pow(2, -10.0f * x));
				}
				else
				{
					return (x == 0.0f ? 0.0f : (x == 1.0f ? 1.0f : (x < 0.5f ? std::pow(2.0f, 20.0f * x - 10.0f) / 2.0f : (2.0f - std::pow(2.0f, -20.0f * x - 10.0f) / 2.0f))));
				}
				break;
			}
			case EasingType::CIR:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return 1.0f - std::sqrt(1.0f - std::pow(x, 2.0f));
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return std::sqrt(1.0f - std::pow(x - 1.0f, 2.0f));
				}
				else
				{
					return (x < 0.5f ? (1.0f - std::sqrt(1.0f - std::pow(2.0f * x, 2.0f))) / 2.0f : (std::sqrt(1.0f - std::pow(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f);
				}
				break;
			}
			case EasingType::BACK:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return c3 * x * x * x - c1 * x * x;
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return 1.0f + c3 * std::pow(x - 1.0f, 3.0f) + c1 * std::pow(x - 1.0f, 2.0f);
				}
				else
				{
					return (x < 0.5f ? (std::pow(2.0f * x, 2.0f) * ((c2 + 1.0f) * 2.0f * x - c2)) / 2.0f : (std::pow(2.0f * x - 2.0f, 2.0f) * ((c2 + 1.0f) * (x * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f);
				}
				break;
			}
			case EasingType::ELASTIC:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return (x == 0.0f ? 0.0f : (x == 1.0f ? 1.0f : -std::pow(2.0f, 10.0f * x - 10.0f) * std::sin((x * 10.0f - 10.75f) * c4)));
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return (x == 0.0f ? 0.0f : (x == 1.0f ? 1.0f : std::pow(2.0f, -10.0f * x) * std::sin((x * 10.0f - 0.75f) * c4) + 1.0f));
				}
				else
				{
					return (x == 0.0f ? 0.0f : (x == 1.0f ? 1.0f : (x < 0.5f ? -(std::pow(2.0f, 20.0f * x - 10.0f) * std::sin((20.0f * x - 11.125f) * c5)) / 2.0f :
						(std::pow(2.0f, -20.0f * x + 10.0f) * std::sin((20.0f * x - 11.125f) * c5)) / 2.0f + 1.0f)));
				}
				break;
			}
			case EasingType::BOUNCE:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return 1.0f - easeOutBounce(1.0f - x);
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return easeOutBounce(x);
				}
				else
				{
					return (x < 0.5f ? (1.0f - easeOutBounce(1.0f - 2.0f * x)) / 2.0f : (1.0f + easeOutBounce(2.0f * x - 1.0f)) / 2.0f);
				}
				break;
			}
			default:
			{
				return x;
				break;
			}
			};
		}

		float easeOutBounce(float x)
		{
			if (x < 1.0f / d1)
			{
				return n1 * x * x;
			}
			else if (x < 2.0f / d1)
			{
				return n1 * (x -= 1.5f / d1) * x + 0.75f;
			}
			else if (x < 2.5f / d1)
			{
				return n1 * (x -= 2.25f / d1) * x + 0.9375f;
			}
			else
			{
				return n1 * (x -= 2.625f / d1) * x + 0.984375f;
			}
		}

		T pos;

		T target;

		float ease;

		float delta;

		float speed;

		std::function<void()> finished_callback;

		std::function<void(T)> update_callback;

		bool complete;

		EasingType type;

		EasingMode mode;

		double epsilon;

		const float c1 = 1.70158f;
		const float c2 = c1 * 1.525f;
		const float c3 = c1 + 1.0f;
		const float c4 = (2.0f * PI) / 3.0f;
		const float c5 = (2.0f * PI) / 4.5f;
		const float n1 = 7.5625f;
		const float d1 = 2.75f;
	};

	template<typename T>
	class TweenList
	{
	public:

		TweenList() : repeat(false), complete(true) { }

		TweenList(const std::vector<T>& _list, bool _repeat)
		{
			setList(_list, _repeat);
		}

		void setList(const std::vector<T>& _list, bool _repeat)
		{
			list = _list;
			backup = _list;
			repeat = _repeat;
			if (_list.size() > 0)
			{
				complete = false;
				tween.setTarget((*_list.begin()));
			}
		}

		bool update(double dt)
		{
			if (tween.update(dt) && !complete)
			{
				if (list.size() > 0)
				{
					list.erase(list.begin());

					if (!list.empty())
					{
						tween.setTarget((*list.begin()));
						complete = false;
					}
					else
					{
						if (repeat)
						{
							list = backup;
							tween.setTarget((*list.begin()));
							complete = false;
						}
						else
						{
							complete = true;
						}
					}
				}
				else
				{
					complete = true;
				}
			}
			return complete;
		}

		void operator=(const TweenList<T> other)
		{
			tween = other.tween;
			list = other.list;
			backup = other.backup;
			repeat = other.repeat;
			complete = other.complete;
		}

		Tween<T>& getTween()
		{
			return tween;
		}

	private:

		Tween<T> tween;

		std::vector<T> list;

		std::vector<T> backup;

		bool repeat;

		bool complete;

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

		std::mutex lock;

		std::condition_variable cv;

		bool quit;

		std::vector<std::thread> threads;

		std::queue<FuncPtr> tasks;

	};

};