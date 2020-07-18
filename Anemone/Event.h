#pragma once

namespace ae
{
	enum class EventType
	{
		WindowClose, WindowResize, WindowFocus,
		KeyPressed, KeyReleased, KeyTyped,
		MouseDown, MouseRelease, MouseMove, MouseScroll
	};
	
	#define EVENT_TYPE(type) EventType GetType() const override { return EventType::type; }

	struct Event
	{
		virtual EventType GetType() const = 0;
	};

	struct WindowCloseEvent : public Event
	{
		EVENT_TYPE(WindowClose);
	};

	struct WindowResizeEvent : public Event
	{
		unsigned int width, height;
		
		WindowResizeEvent(unsigned int _width, unsigned int _height) : width(_width), height(_height){}

		EVENT_TYPE(WindowResize);
	};

	struct WindowFocus : public Event
	{
		int entered;

		WindowFocus(int _entered) : entered(_entered){}

		EVENT_TYPE(WindowFocus);
	};

	struct KeyPressedEvent : public Event
	{
		int key, scancode, mods;
		bool repeated;

		KeyPressedEvent(int _key, int _scancode, int _mods, bool _repeated) : key(_key), scancode(_scancode), mods(_mods), repeated(_repeated){}

		EVENT_TYPE(KeyPressed);
	};

	struct KeyReleasedEvent : public Event
	{
		int key, scancode, mods;

		KeyReleasedEvent(int _key, int _scancode, int _mods) : key(_key), scancode(_scancode), mods(_mods){}

		EVENT_TYPE(KeyReleased);
	};

	struct KeyTypedEvent : public Event
	{
		unsigned int codepoint;

		KeyTypedEvent(unsigned int _codepoint) : codepoint(_codepoint) {}

		EVENT_TYPE(KeyTyped);
	};

	struct MouseDownEvent : public Event
	{
		int button, mods;

		MouseDownEvent(int _button, int _mods) : button(_button), mods(_mods) {}

		EVENT_TYPE(MouseDown);
	};

	struct MouseReleaseEvent : public Event
	{
		int button, mods;

		MouseReleaseEvent(int _button, int _mods) : button(_button), mods(_mods) {}

		EVENT_TYPE(MouseRelease);
	};

	struct MouseMoveEvent : public Event
	{
		float xpos, ypos;

		MouseMoveEvent(float _xpos, float _ypos) : xpos(_xpos), ypos(_ypos) {}

		EVENT_TYPE(MouseMove);
	};

	struct MouseScrollEvent : public Event
	{
		float x_offset, y_offset;

		MouseScrollEvent(float _x_offset, float _y_offset) : x_offset(_x_offset), y_offset(_y_offset) {}

		EVENT_TYPE(MouseScroll);
	};
}