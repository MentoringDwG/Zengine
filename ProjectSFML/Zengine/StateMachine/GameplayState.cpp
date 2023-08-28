#include "GameplayState.h"

#include <iostream>

void GameplayState::OnEnter(int prevStateId)
{
	std::cout << "Gameplay State enter" << std::endl;
}

void GameplayState::OnLeave(int nextStateId)
{

}