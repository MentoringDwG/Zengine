#pragma once

#include "BaseGameState.h"

class MainMenuState: public BaseGameState 
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnLeave(int nextStateId) override;

	MainMenuState(int stateIdIn) : BaseGameState(stateIdIn)
	{

	}
};

