#include "GameplayState.h"
#include <Zengine/Zengine.h>

void GameplayState::OnEnter(int prevStateId)
{

}

void GameplayState::OnUpdate()
{

}

void GameplayState::OnLeave(int nextStateId)
{
	 Zengine::GetInstance()->gameMode = false;
}