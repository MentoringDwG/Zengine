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
		//zenObject = new ZenObject(10, "Ground", sf::Vector2f(960, 64));

		//boxCollider = new BoxCollider2D(new Vector2(position.x, position.y), new Vector2(960,64), zenObject);
		//listenerIndex = boxCollider->OnCollisionStart.AddListener(&Ground::HandleCollisionStart, this);
		//ZenPhysics2D::Get()->RegisterCollider(boxCollider);
	}

	void SetBoxColliders(string pathToGroundTxt);

private:
	sf::Vector2f position;
	std::vector<BoxCollider2D*> boxColliders;

	std::vector<ZenObject*> zenObjects;

	void HandleCollisionStart(Collider* other)
	{

	}

	int listenerIndex;
};

