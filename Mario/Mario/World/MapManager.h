#pragma once

#include <map>
#include "../../../nlohmann/json.hpp"
#include <Zengine/Renderer/Renderer.h>

class Map;

class MapManager
{
public:
	void AddMap(int id, Map* map, std::string pathToTexturesTxt, int rows, int columns, nlohmann::json tileMapData);
	Map* LoadMap(int id, RenderingStack* renderStack, class World* world);
private:
	std::map <int, Map*> maps;
};

