#include "..\Anemone\Event.h"

namespace ae
{
	namespace Input
	{
		namespace
		{
			vec2 mouse_pos;
			bool keys[GLFW_KEY_LAST];
		};

		const vec2& getMousePos()
		{
			return mouse_pos;
		}

		const void setMousePos(const ae::vec2& new_mouse_pos)
		{
			mouse_pos = new_mouse_pos;
		}

		const bool keyIsDown(unsigned int key)
		{
			return keys[key];
		}
	};
};