#include "GameplayState.h"

#include <iostream>

void GameplayState::OnEnter(int prevStateId)
{
	std::cout << "Gameplay State enter" << std::endl;
}

void GameplayState::OnUpdate()
{

}

void GameplayState::OnLeave(int nextStateId)
{

}