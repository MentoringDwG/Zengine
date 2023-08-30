#pragma once

#include "BaseGameState.h"
#include "../ZenObject/ZenShape.h"
#include "../Renderer/Renderer.h"
#include "../UI/UIButton.h"
#include "../InputModule/UIInputHandler.h"
#include "WaitingRoomState.h"

class ControlsPanelState: public BaseGameState
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	ControlsPanelState(int stateIdIn, RenderingStack* renderStackIn, StateMachine* stateMachineIn) : BaseGameState(stateIdIn), renderStack(renderStackIn), stateMachine(stateMachineIn) {}

private:
	ZenShape* contolsPanel = nullptr;
	sf::Texture* contolsPanelTexture = nullptr;
	RenderObject* contolsPanelRenderObject = nullptr;
	RenderingStack* renderStack;
	UIButton* back = nullptr;
	WaitingRoomState* waitingRoomState = nullptr;
	StateMachine* stateMachine = nullptr;

	void BackToMainMenu(int id);
};

