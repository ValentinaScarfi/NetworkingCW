#include "stdafx.h"
#include "StateMachine.h"


void StateMachine::ChangeState(StateRef newState)
{
	//New state replace current
	this->isAdding = true;

	//saving new state
	this->newState = std::move(newState);
}

void StateMachine::ProcessStateChanges()
{
	if (this->isAdding)
	{
		//changing state
		this->currentState = std::move(this->newState);
		//initialise state
		this->currentState->Init();
		//not adding anymore
		this->isAdding = false;
	}
}

StateRef & StateMachine::GetActiveState()
{
	return currentState;
}
