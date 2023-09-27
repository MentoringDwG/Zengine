#include "LoadingState.h"
#include <Zengine/StateMachine/StateMachine.h>

LoadingState::LoadingState(int stateIdIn, StateMachine* stateMachine) : BaseGameState(stateIdIn)
{
	this->stateMachine = stateMachine;
}

void LoadingState::OnEnter(int prevStateId)
{
	OnEnterEvent(2);
}

void LoadingState::OnUpdate()
{

}

void LoadingState::OnLeave(int nextStateId)
{

}