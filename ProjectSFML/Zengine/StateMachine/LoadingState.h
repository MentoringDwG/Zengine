#pragma once

#include "BaseGameState.h"
#include "../Renderer/Renderer.h"
#include "../StateMachine/StateMachine.h"
#include <functional>
#include "WaitingRoomState.h"

class LoadingState : public BaseGameState
{
private:
	RenderingStack* renderStack;
	StateMachine* stateMachine;

public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	std::function<void(int)> OnEnterEvent;

	LoadingState(int stateIdIn, RenderingStack* renderStack, StateMachine* stateMachine);
};

