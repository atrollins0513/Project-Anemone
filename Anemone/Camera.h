#pragma once

#include "Error.h"
#include "Math.h"
#include "Event.h"
#include "Utilities.h"

namespace ae
{
	class Camera
	{
	public:

		Camera() = default;

		Camera(unsigned int width, unsigned int height);

		void update(double dt);

		void event(Event& e);

		void setDragButton(int button);

		void track(vec3* tracked_object_position);

		void stopTracking();

		void setTweens(std::vector<vec3> list, bool repeat);

		void setTarget(const vec3& target);

		ae::mat4& getProj() { return proj; }

		ae::mat4& getView() { return view; }

		const vec3& getTranslation() const { return translation; }

		Tween<vec3>& getTween();

	private:
		
		vec3 old_position;
		vec3 translation;
		mat4 proj;
		mat4 view;
		vec3* tracked		{ nullptr };
		bool mouse_down		{ false };
		float total_zoom	{ 1.0f };
		int drag_button		{ GLFW_MOUSE_BUTTON_MIDDLE };
		TweenList<vec3> tweenList;

	};
};