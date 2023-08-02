#pragma once

#include "../Physics2D/ZenPhysics2D.h"
#include "../Colliders/BoxCollider2D.h"
#include "../ZenObject/ZenObject.h"

class Ground
{
public:
	Ground(sf::Vector2f position)
	{
		this->position = position;
		zenObject = new ZenObject(10, "Ground", sf::Vector2f(960, 64));

		boxCollider0 = new BoxCollider2D(new Vector2(position.x, position.y), new Vector2(960, 64), zenObject);
		boxCollider0->OnBoxCollisionStart = std::bind(&Ground::HandleBoxCollisionStart, this, std::placeholders::_1);
		ZenPhysics2D::Get()->RegisterCollider(boxCollider0);
	}

private:
	sf::Vector2f position;
	std::vector <BoxCollider2D*> boxColliders2D;
	BoxCollider2D* boxCollider0 = nullptr;

	ZenObject* zenObject = nullptr;

	void HandleBoxCollisionStart(BoxCollider2D* other)
	{

	}
};

