#pragma once

#include <Zengine/StateMachine/BaseGameState.h>
#include <Zengine/Renderer/Renderer.h>

class StateMachine;

class ControlsPanelState: public BaseGameState
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	ControlsPanelState(int stateIdIn, RenderingStack* renderStackIn, StateMachine* stateMachineIn) : BaseGameState(stateIdIn), renderStack(renderStackIn), stateMachine(stateMachineIn) {}
	~ControlsPanelState();

private:
	void BackToMainMenu(int id);

	class ZenShape* contolsPanel = nullptr;
	sf::Texture* contolsPanelTexture = nullptr;
	RenderObject* contolsPanelRenderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	class UIButton* back = nullptr;
	class WaitingRoomState* waitingRoomState = nullptr;
	StateMachine* stateMachine = nullptr;
};

