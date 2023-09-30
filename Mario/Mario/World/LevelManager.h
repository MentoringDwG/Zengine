#pragma once

#include <map>
#include <Zengine/World/World.h>

class LevelManager
{
public:
	void AddLevel(int id, World* level);
	void DeleteLevel(int id);
	World* GetLevel(int id);
private:
	std::map<int, World*> levels;
};

