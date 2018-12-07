#include "stdafx.h"
#include "StateMachine.h"


void StateMachine::ChangeState(StateRef newState)
{
	//New state replace current -> to change state only once in the game loop
	this->isChangingState = true;

	//saving new state
	this->newState = std::move(newState);
}

void StateMachine::ProcessStateChanges()
{
	if (this->isChangingState)
	{
		//changing state
		this->currentState = std::move(this->newState);
		//initialise state
		this->currentState->Init();
		//not adding anymore
		this->isChangingState = false;
	}
}

StateRef & StateMachine::GetActiveState()
{
	return currentState;
}
