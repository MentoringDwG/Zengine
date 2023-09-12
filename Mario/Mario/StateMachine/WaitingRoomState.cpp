#include "WaitingRoomState.h"

void WaitingRoomState::OnEnter(int prevStateId)
{
	clock.restart();
}

void WaitingRoomState::OnUpdate()
{
	if (clock.getElapsedTime().asMilliseconds() > 100)
	{
		stateMachine->TransitionTo(transitionStateId);
	}
}

void WaitingRoomState::OnLeave(int nextStateId)
{
	delete this;
}

WaitingRoomState::WaitingRoomState(int stateIdIn, StateMachine* stateMachine, int transitionStateId) : BaseGameState(stateIdIn)
{
	this->stateMachine = stateMachine;
	this->transitionStateId = transitionStateId;
}