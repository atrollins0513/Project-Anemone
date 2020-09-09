#include "..\Anemone\Camera.h"

namespace ae
{

	Camera::Camera(unsigned int width, unsigned int height) : Camera()
	{
		proj = Ortho((float)width, (float)height);
	}

	void Camera::update(double dt)
	{
		if (tracked != nullptr)
		{
			translation = *tracked;
		}
		else
		{
			if (!tweenList.update(dt))
			{
				translation += tweenList.getTween().getPos();
			}
		}

		view = translate(translation);
	}

	void Camera::event(Event& e)
	{
		ae::vec3 mouse_pos = Input::getMousePos();

		switch (e.GetType())
		{
		case ae::EventType::MouseDown:
		{
			auto md = (ae::MouseDownEvent&)(e);
			if (md.button == drag_button)
			{
				old_position = mouse_pos;
				mouse_down = true;
			}
			break;
		}
		case ae::EventType::MouseRelease:
		{
			auto md = (ae::MouseDownEvent&)(e);
			if (md.button == drag_button)
			{
				mouse_down = false;
			}
			break;
		}
		case ae::EventType::MouseMove:
		{
			if (mouse_down)
			{
				translation += mouse_pos - old_position;
				view = translate((mouse_pos - old_position) / total_zoom) * view;
				old_position = mouse_pos;
			}
			break;
		}
		case ae::EventType::MouseScroll:
		{
			float zoom = (((ae::MouseScrollEvent&)e).y_offset == 1 ? 1.1f : 0.9f);
			total_zoom *= zoom;
			view = translate((mouse_pos - translation) * -1.0f) * ae::scale(zoom, zoom, 0.0f) * translate(mouse_pos - translation) * view;
			break;
		}
		};
	}

	void Camera::setDragButton(int button)
	{
		drag_button = button;
	}

	void Camera::track(vec3* tracked_object_position)
	{
		tracked = tracked_object_position;
	}

	void Camera::stopTracking()
	{
		tracked = nullptr;
	}

	void Camera::setTweens(std::vector<vec3> list, bool repeat)
	{
		tweenList.setList(list, repeat);
	}

	void Camera::setTarget(const vec3& target)
	{
		tweenList.setList({ target }, false);
	}

	Tween<vec3>& Camera::getTween()
	{
		return tweenList.getTween();
	}

};