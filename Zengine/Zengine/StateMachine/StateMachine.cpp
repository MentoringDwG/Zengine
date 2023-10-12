// Copyright Z.Z. Zengine (c)

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

		int currentId = CurrentGameState->GetStateId();
		CurrentGameState = NextState;
		currentGameStateId = stateId;

		CurrentGameState->OnEnter(currentId);
	}
	else
	{
		CurrentGameState = NextState;
		currentGameStateId = stateId;

		CurrentGameState->OnEnter(0);
	}
}

void StateMachine::Update()
{
	if (CurrentGameState == nullptr) return;

	CurrentGameState->OnUpdate();
}

BaseGameState* StateMachine::GetCurrentGameState()
{
	return CurrentGameState;
}

int StateMachine::GetCurrentGameStateId()
{
	return currentGameStateId;
}
void StateMachine::DeleteState(int stateId)
{
	GameStates.erase(stateId);
}