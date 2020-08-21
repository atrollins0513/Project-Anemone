#include "..\Anemone\State.h"

namespace ae
{

	void StateManager::addState(unsigned int id, State* state, bool set_current, bool initialize)
	{
		assert(!stateExists(id), "A state already exists for this id.");
		states.emplace(id, state);
		if (set_current) { current_state = state; }
		if (initialize) { state->init(); }
	}

	void StateManager::removeState(unsigned int id, bool cleanup)
	{
		assert(stateExists(id), "State does not exist.");
		states.at(id)->destroy();
		if (cleanup) { delete states.at(id); }
		states.erase(id);
	}

	void StateManager::setState(unsigned int id, bool initialize)
	{
		assert(stateExists(id), "State does not exist.");
		current_state = states.at(id);
		if (initialize) { current_state->init(); }
	}

	void StateManager::setState(unsigned int id, State* state, bool initialize)
	{
		assert(!stateExists(id), "A state already exists for this id.");
		states.emplace(id, state);
		current_state = state;
		if (initialize) { current_state->init(); }
	}

	State* StateManager::getState(unsigned int id)
	{
		assert(stateExists(id), "State does not exist.");
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