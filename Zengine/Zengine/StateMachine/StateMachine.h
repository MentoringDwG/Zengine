// Copyright Z.Z. Zengine (c)

#pragma once

#include <iostream>
#include <map>

namespace State
{
	enum EAppState
	{
		None = 0,
		MainMenuState = 1,
		LoadingState = 2,
		GameplayState = 3,
		WaitingRoomState = 4,
		ControlsPanelState = 5,
		AuthorsState = 6,
		GameOverState = 7,
		WinState = 8,
		Max,
	};
}

class StateMachine
{
private:
	std::map<int, class BaseGameState*> GameStates;
	int currentGameStateId = 0;
	BaseGameState* CurrentGameState = nullptr;

public:
	bool AddState(BaseGameState* gameState);
	void DeleteState(int stateId);
	void TransitionTo(int stateId);
	void Update();
	BaseGameState* GetCurrentGameState();
	int GetCurrentGameStateId();
};

