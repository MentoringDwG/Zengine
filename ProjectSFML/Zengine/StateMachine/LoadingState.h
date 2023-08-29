#pragma once

#include "BaseGameState.h"

class LoadingState : public BaseGameState
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	LoadingState(int stateIdIn) : BaseGameState(stateIdIn)
	{

	}
};

