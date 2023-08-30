#pragma once

#include "BaseGameState.h"
#include "StateMachine.h"
#include <SFML/Graphics.hpp>

class WaitingRoomState : public BaseGameState
{
public:
	virtual void OnEnter(int prevStateId) override;
	virtual void OnUpdate() override;
	virtual void OnLeave(int nextStateId) override;

	WaitingRoomState(int stateIdIn, StateMachine* stateMachine, int transitionStateId);

private:
	StateMachine* stateMachine = nullptr;
	int transitionStateId;
	sf::Clock clock;
};

