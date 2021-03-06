#include "..\Anemone\Event.h"

namespace ae
{
	vec2 Input::mouse_pos			= 0.0f;
	bool Input::keys[GLFW_KEY_LAST]	{ false };

	const vec2& Input::getMousePos()
	{
		return mouse_pos;
	}

	const void Input::setMousePos(const ae::vec2& new_pos)
	{
		mouse_pos = new_pos;
	}

	const bool Input::keyIsDown(unsigned int key)
	{
		return keys[key];
	}
};