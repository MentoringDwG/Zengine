#pragma once

#include <Zengine/StateMachine/BaseGameState.h>
#include <Zengine/Renderer/Renderer.h>

class StateMachine;

class GameOverState : public BaseGameState
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	GameOverState(int stateIdIn, RenderingStack* renderStackIn, StateMachine* stateMachineIn);
	~GameOverState();

private:
	void BackToMainMenu(int id);

	class ZenShape* gameOverPanel = nullptr;
	sf::Texture* panelTexture = nullptr;
	RenderObject*panelRenderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	class UIButton* back = nullptr;
	class WaitingRoomState* waitingRoomState = nullptr;
	StateMachine* stateMachine = nullptr;
};

