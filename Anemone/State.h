#pragma once

#include <memory>
#include <unordered_map>
#include <tuple>
#include <assert.h>
#include <string>

#ifndef GLEW_STATIC
	#define GLEW_STATIC
#endif

#include "includes\glew.h"
#include "includes\glfw3.h"

#include "Utilities.h"
#include "Event.h"

namespace ae
{

	struct Scene
	{
		virtual void update(double dt) = 0;
		virtual void render() = 0;
	};

	class State
	{
	public:

		virtual void init() = 0;

		virtual void update(double dt) = 0;

		virtual void render(double alpha) = 0;

		virtual void event(ae::Event& e) = 0;

		virtual void destroy() = 0;

		bool addScene(unsigned int id, Scene* scene)
		{
			if (scenes.find(id) == scenes.end())
			{
				scenes.emplace(id, scene);
				return true;
			}
			return false;
		}

		Scene* getScene(unsigned int id)
		{
			if (scenes.find(id) == scenes.end())
			{
				return nullptr;
			}
			return scenes.at(id);
		}

		void removeScene(unsigned int id)
		{
			if (scenes.find(id) != scenes.end())
			{
				delete scenes.at(id);
				scenes.erase(id);
			}
		}

		void updateScenes(double dt)
		{
			for (auto& s : scenes)
			{
				s.second->update(dt);
			}
		}

		void renderScenes()
		{
			for (auto& s : scenes)
			{
				s.second->render();
			}
		}

	protected:

		std::unordered_map<unsigned int, Scene*> scenes;

	};
	
	class StateManager
	{
	public:

		StateManager() : current_state(nullptr) {}

		void addState(unsigned int id, State* state, bool set_current = false, bool initialize = false);

		void removeState(unsigned int id, bool cleanup);

		void setState(unsigned int id, bool initialize = false);

		void setState(unsigned int id, State* state, bool initialize = false);

		State* getState(unsigned int id);

		State* getCurrentState();

		bool stateExists(unsigned int id);

	protected:

		State* current_state;

		std::unordered_map<unsigned int, State*> states;

	};

};