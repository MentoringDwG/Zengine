#pragma once

#include <iostream>
#include <map>

class StateMachine
{
private:
	std::map<int, class BaseGameState*> GameStates;
	BaseGameState* CurrentGameState;
	int currentGameStateId = 0;

public:
	bool AddState(BaseGameState* gameState);
	void DeleteState(int stateId);
	void TransitionTo(int stateId);
	void Update();
	BaseGameState* GetCurrentGameState();
	int GetCurrentGameStateId();
};

