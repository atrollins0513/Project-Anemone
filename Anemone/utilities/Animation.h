#pragma once

#include <vector>
#include <functional>

namespace ae
{
	struct Frame
	{

		float u				{ 0.0f };
		float v				{ 0.0f };
		float uw			{ 0.0f };
		float vh			{ 0.0f };
		float limit			{ 0.0f };
		unsigned int index	{ 0 };

		Frame(float _u, float _v, float _uw, float _vh, float _limit) : limit(_limit), u(_u), v(_v), uw(_uw), vh(_vh), index(0) { }

		Frame(unsigned int _index, float _limit) : limit(_limit), u(0.0f), v(0.0f), uw(0.0f), vh(0.0f), index(_index) { }

	};

	class Animation
	{
	public:

		bool update(double dt);

		void addFrame(Frame frame);

		const Frame& getCurrentFrame() const;

		void setCurrentFrame(unsigned int _frame_index);

		void reset();

	private:

		double time					{ 0.0 };

		unsigned int frame_index	{ 0 };

		std::vector<Frame> frames;

	};

	// Tweening

	enum class EasingType { LINEAR, SINE, QUAD, CUBIC, QUART, QUINT, EXP, CIR, BACK, ELASTIC, BOUNCE };

	enum class EasingMode { EASE_IN = 0, EASE_OUT, EASE_INOUT };

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

		bool complete{ true };
		float ease{ 0.0f };
		float delta{ 0.0f };
		float speed{ 0.0f };
		double epsilon{ 0.0 };
		EasingType type{ EasingType::SINE };
		EasingMode mode{ EasingMode::EASE_INOUT };
		const float c1{ 1.70158f };
		const float c2{ c1 * 1.525f };
		const float c3{ c1 + 1.0f };
		const float c4{ (float)((2.0f * PI) / 3.0f) };
		const float c5{ (float)((2.0f * PI) / 4.5f) };
		const float n1{ 7.5625f };
		const float d1{ 2.75f };
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

		bool repeat{ false };
		bool complete{ true };
		Tween<T> tween;
		std::vector<T> list;
		std::vector<T> backup;

	};
}
