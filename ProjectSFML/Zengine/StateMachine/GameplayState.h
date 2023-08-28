#pragma once

#include "BaseGameState.h"

class GameplayState: public BaseGameState
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnLeave(int nextStateId) override;

	GameplayState(int stateIdIn) : BaseGameState(stateIdIn)
	{

	}
};

