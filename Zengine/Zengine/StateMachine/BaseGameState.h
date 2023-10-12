// Copyright Z.Z. Zengine (c)

#pragma once

class BaseGameState
{
private:
	int stateId;

public:
	BaseGameState(int stateIdIn) : stateId(stateIdIn) {}

	virtual void OnEnter(int prevStateId) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnLeave(int nextStateId) = 0;

	int GetStateId();
};

