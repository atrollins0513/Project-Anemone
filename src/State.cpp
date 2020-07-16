#include "..\Anemone\State.h"

namespace ae
{

	void StateManager::removeState(unsigned int id)
	{
		if (stateExists(id))
		{
			states.erase(id);
		}
	}

	void StateManager::setState(unsigned int id, bool initialize, bool transitionIn)
	{
		if (stateExists(id))
		{
			current_state = states.at(id);

			if (initialize)
			{
				current_state->init();
			}

			if (transitionIn)
			{
				current_state->transitionIn();
			}
		}
	}

	std::shared_ptr<State> StateManager::getState(unsigned int id)
	{
		return states.at(id);
	}

	std::shared_ptr<State> StateManager::getCurrentState()
	{
		return current_state;
	}

	bool StateManager::stateExists(unsigned int id)
	{
		return (states.find(id) != states.end());
	}

};