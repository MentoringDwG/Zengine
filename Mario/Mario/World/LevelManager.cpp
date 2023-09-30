#include "LevelManager.h"

void LevelManager::AddLevel(int id, World* level)
{
	levels[id] = level;
}

void LevelManager::DeleteLevel(int id)
{
	levels.erase(id);
}

World* LevelManager::GetLevel(int id)
{
	return levels[id];
}