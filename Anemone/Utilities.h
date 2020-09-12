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
#include <exception>

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

	template<typename T>
	struct MakeSmartExt
	{
		template<typename ... Args>
		static ae::sptr<T> makes(Args&& ... args)
		{
			return ae::makes<T>(std::forward<Args>(args)...);
		}

		template<typename ... Args>
		static ae::uptr<T> makeu(Args&& ... args)
		{
			return ae::makeu<T>(std::forward<Args>(args)...);
		}
	};

	// Error Utilities

	extern void log(const std::string& identifier, const std::string& message);

	extern void log(const std::string& identifier, const std::string& message, const std::string& message_two);

	extern bool toss(bool trigger, const std::string& msg);

	// File Utilities

	extern std::string loadFile(const std::string& filename, int file_mode = std::ios::in);

	// String Utilities

	extern std::vector<std::string> explode(const std::string& s, char delim);

	// Random Function Utilities

	extern void setSeed(int seed);

	extern int random(unsigned int upper_limit);

	extern int random(unsigned int lower_limit, unsigned int upper_limit);

	// Color Utilities

	constexpr vec3 hexToRGB(int hex)
	{
		return vec3(((hex >> 16) & 0xFF) / 255.0f, ((hex >> 8) & 0xFF) / 255.0f, (hex & 0xFF) / 255.0f);
	}

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

	// Tweening

	enum class EasingType { LINEAR, SINE, QUAD, CUBIC, QUART, QUINT, EXP, CIR, BACK, ELASTIC, BOUNCE };

	enum class EasingMode { EASE_IN = 0 , EASE_OUT, EASE_INOUT };

	template<typename T>
	class Tween
	{
	public:

		Tween() = default;

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

	private:

		float easingDelta(float x)
		{
			switch (type)
			{
			case EasingType::SINE:
			{
				if (mode == EasingMode::EASE_IN)
				{
					return 1.0f - (float)cos((x * PI) / 2.0f);
				}
				else if (mode == EasingMode::EASE_OUT)
				{
					return (float)sin((x * PI) / 2.0f);
				}
				else
				{
					return (float)-(cos(PI * x) - 1.0f) / 2.0f;
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
					return (x == 1.0f ? 1.0f : 1.0f - (float)std::pow(2, -10.0f * x));
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

		bool complete		{ true };
		float ease			{ 0.0f };
		float delta			{ 0.0f };
		float speed			{ 0.0f };
		double epsilon		{ 0.0 };
		EasingType type		{ EasingType::SINE };
		EasingMode mode		{ EasingMode::EASE_INOUT };
		const float c1		{ 1.70158f };
		const float c2		{ c1 * 1.525f };
		const float c3		{ c1 + 1.0f };
		const float c4		{ (float)((2.0f * PI) / 3.0f) };
		const float c5		{ (float)((2.0f * PI) / 4.5f) };
		const float n1		{ 7.5625f };
		const float d1		{ 2.75f };
		T pos;
		T target;
		std::function<void()> finished_callback;
		std::function<void(T)> update_callback;
	};

	template<typename T>
	class TweenList
	{
	public:

		TweenList() = default;

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

		Tween<T>& getTween()
		{
			return tween;
		}

	private:

		bool repeat		{ false };
		bool complete	{ true };
		Tween<T> tween;
		std::vector<T> list;
		std::vector<T> backup;

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