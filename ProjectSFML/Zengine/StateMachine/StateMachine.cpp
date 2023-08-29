#include "StateMachine.h"
#include "BaseGameState.h"

bool StateMachine::AddState(BaseGameState* gameState)
{
	if (GameStates.find(gameState->GetStateId()) == GameStates.end())
	{
		GameStates[gameState->GetStateId()] = gameState;
		return true;
	}
	else
	{
		return false;
	}
}

void StateMachine::TransitionTo(int stateId)
{
	if (GameStates.find(stateId) == GameStates.end())
	{
		std::cout << "State doesn`t exist";
		return;
	}

	BaseGameState* NextState = GameStates[stateId];

	if (CurrentGameState != nullptr)
	{
		CurrentGameState->OnLeave(stateId);
		NextState->OnEnter(CurrentGameState->GetStateId());
	}
	else
	{
		NextState->OnEnter(0);
	}
	
	CurrentGameState = NextState;
}

void StateMachine::Update()
{
	CurrentGameState->OnUpdate();
}