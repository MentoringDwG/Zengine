#pragma once

#include "../../../Zengine/Zengine/StateMachine/BaseGameState.h"
#include "../../../Zengine/Zengine/StateMachine/StateMachine.h"
#include <SFML/Graphics.hpp>

class WaitingRoomState : public BaseGameState
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	WaitingRoomState(int stateIdIn, StateMachine* stateMachine, int transitionStateId);

private:
	sf::Clock clock;
	int transitionStateId;
	StateMachine* stateMachine = nullptr;
};

