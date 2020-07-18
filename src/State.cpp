#include "..\Anemone\State.h"

namespace ae
{

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

	std::shared_ptr<State> StateManager::getState(const std::string& name)
	{
		return states.at(name);
	}

	std::shared_ptr<State> StateManager::getCurrentState()
	{
		return current_state;
	}

	bool StateManager::stateExists(const std::string& name)
	{
		return (states.find(name) != states.end());
	}

};