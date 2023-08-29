#pragma once

#include <iostream>
#include <map>

class StateMachine
{
private:
	std::map<int, class BaseGameState*> GameStates;
	BaseGameState* CurrentGameState;

public:
	bool AddState(BaseGameState* gameState);
	void TransitionTo(int stateId);
	void Update();
};

