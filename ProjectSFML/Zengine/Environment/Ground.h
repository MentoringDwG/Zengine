#pragma once

#include "../Physics2D/ZenPhysics2D.h"
#include "../Colliders/BoxCollider2D.h"
#include "../ZenObject/ZenObject.h"

class Ground
{
public:
	Ground(string pathToGroundTxt)
	{
		SetBoxColliders(pathToGroundTxt);
	}

	void SetBoxColliders(string pathToGroundTxt);

private:
	sf::Vector2f position;
	std::vector<BoxCollider2D*> boxColliders;

	std::vector<ZenObject*> zenObjects;

	void HandleCollisionStart(Collider* other);

	int listenerIndex;
};

