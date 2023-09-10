#pragma once

#include "BaseGameState.h"
#include "../Renderer/Renderer.h"

class StateMachine;

class AuthorsState: public BaseGameState
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	AuthorsState(int stateIdIn, RenderingStack* renderStackIn, StateMachine* stateMachineIn) : BaseGameState(stateIdIn), renderStack(renderStackIn), stateMachine(stateMachineIn) {}
	~AuthorsState();

private:
	void BackToMainMenu(int id);

	class ZenShape* authorsPanel = nullptr;
	sf::Texture* authorsPanelTexture = nullptr;
	RenderObject* authorsPanelRenderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	class UIButton* back = nullptr;
	class WaitingRoomState* waitingRoomState = nullptr;
	StateMachine* stateMachine = nullptr;
};

