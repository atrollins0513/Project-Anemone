#include "..\Anemone\State.h"

namespace ae
{

	void StateManager::addState(unsigned int id, State* state, bool set_current, bool initialize)
	{
		toss(stateExists(id), "A state already exists for id " + std::to_string(id));
		states.emplace(id, state);
		if (set_current) { current_state = state; }
		if (initialize) { state->init(); }
	}

	void StateManager::removeState(unsigned int id)
	{
		toss(!stateExists(id), "State at id " + std::to_string(id) + " does not exist.");
		delete states.at(id);
		states.erase(id);
	}

	void StateManager::setState(unsigned int id, bool initialize)
	{
		toss(!stateExists(id), "State at id " + std::to_string(id) + " does not exist.");
		current_state = states.at(id);
		if (initialize) { current_state->init(); }
	}

	State* StateManager::getState(unsigned int id)
	{
		toss(!stateExists(id), "State at id " + std::to_string(id) + " does not exist.");
		return states.at(id);
	}

	State* StateManager::getCurrentState()
	{
		return current_state;
	}

	bool StateManager::stateExists(unsigned int id)
	{
		return (states.find(id) != states.end());
	}

};