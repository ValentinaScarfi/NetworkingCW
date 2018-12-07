#pragma once

#include <memory>
#include <stack>
#include "State.h"

typedef std::unique_ptr<State> StateRef;

class StateMachine
{
public:
	StateMachine() { }
	~StateMachine() { }

	void ChangeState(StateRef newState);

	//Run at start of each loop in Game.cpp
	void ProcessStateChanges();

	StateRef &GetActiveState();

private:
	std::stack<StateRef> allStates;
	StateRef currentState;
	StateRef newState;

	bool isAdding;
};

