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

	//run at start of game loop. If state changed, the Init() is called only once.
	void ProcessStateChanges();

	StateRef &GetActiveState();

private:
	std::stack<StateRef> allStates;
	StateRef currentState;
	StateRef newState;

	bool isChangingState;
};

