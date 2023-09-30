#pragma once

#include <Zengine/ZenObject/ZenObject.h>
#include "../../../nlohmann\json.hpp"

class Ground
{
public:
	Ground(nlohmann::json groundData)
	{
		SetBoxColliders(groundData);
	}

	~Ground();

	void SetBoxColliders(nlohmann::json groundData);

private:
	void HandleCollisionStart(class Collider* other);
	sf::Vector2f position;
	std::vector<class BoxCollider2D*> boxColliders;
	std::vector<ZenObject*> zenObjects;
	int listenerIndex = 0;

	const int TILE_SCALE = 2;
};

