#include "MainMenuState.h"

#include <iostream>

void MainMenuState::OnEnter(int prevStateId)
{
	std::cout << "Main Menu enter" << std::endl;
}

void MainMenuState::OnLeave(int nextStateId)
{
	std::cout << "Main Menu leave" << std::endl;
}