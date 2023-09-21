#pragma once

#include "../../../Zengine/Zengine/StateMachine/BaseGameState.h"
#include "../../../Zengine/Zengine/Renderer/Renderer.h"

class GameplayState: public BaseGameState
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	GameplayState(int stateIdIn, RenderingStack* renderStackIn) : BaseGameState(stateIdIn), renderStack(renderStackIn) {}

private:
	RenderingStack* renderStack = nullptr;
};

