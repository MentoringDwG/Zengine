#include "LoadingState.h"

#include <iostream>

LoadingState::LoadingState(int stateIdIn, StateMachine* stateMachine) : BaseGameState(stateIdIn)
{
	this->stateMachine = stateMachine;
}

void LoadingState::OnEnter(int prevStateId)
{
	std::cout << "Loading state" << std::endl;

	OnEnterEvent(2);
}

void LoadingState::OnUpdate()
{

}

void LoadingState::OnLeave(int nextStateId)
{

}