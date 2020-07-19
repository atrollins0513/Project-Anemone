#include "..\Anemone\State.h"

namespace ae
{

	void StateManager::addState(sptr<State> state)
	{
		assert(!stateExists(state->getName()));
		state->setParent(parent);
		states.emplace(state->getName(), state);
	}

	void StateManager::removeState(const std::string& name)
	{
		if (stateExists(name))
		{
			states.erase(name);
		}
	}

	void StateManager::setState(const std::string& name, bool initialize)
	{
		if (stateExists(name))
		{
			current_state = states.at(name);

			if (initialize)
			{
				current_state->init();
			}
		}
	}

	sptr<State> StateManager::getState(const std::string& name)
	{
		return states.at(name);
	}

	sptr<State> StateManager::getCurrentState()
	{
		return current_state;
	}

	bool StateManager::stateExists(const std::string& name)
	{
		return (states.find(name) != states.end());
	}

};