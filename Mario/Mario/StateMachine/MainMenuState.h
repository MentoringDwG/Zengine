#pragma once

#include "../../../Zengine/Zengine/StateMachine/BaseGameState.h"
#include "../../../Zengine/Zengine/Renderer/Renderer.h"
#include "../UIinGame/MainMenuPanel.h"
#include "../../../Zengine/Zengine/ZenObject/ZenShape.h"

class MainMenuState : public BaseGameState
{
private:
	MainMenuPanel mainMenuPanel;
	int animationId = 0;
	class ZenShape* zenShape = nullptr;
	sf::Texture* texture = nullptr;
	RenderObject* renderObject = nullptr;
	RenderingStack* renderStack = nullptr;
	Renderer* renderer = nullptr;
	StateMachine* stateMachine = nullptr;

	class Animation* animation = nullptr;
	class Animator* animator = nullptr;

public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	MainMenuState(int stateIdIn, RenderingStack* renderStack, class StateMachine* stateMachine, Renderer* renderer);
	~MainMenuState();
};

