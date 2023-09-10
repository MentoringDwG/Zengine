#pragma once

#include "BaseGameState.h"
#include "../Renderer/Renderer.h"
#include <functional>

class StateMachine;

class LoadingState : public BaseGameState
{
private:
	StateMachine* stateMachine = nullptr;

public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	std::function<void(int)> OnEnterEvent;

	LoadingState(int stateIdIn, StateMachine* stateMachine);
};

