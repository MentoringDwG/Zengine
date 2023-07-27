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
		zenObject = new ZenObject(10, "Ground", sf::Vector2f(64, 64));
		boxCollider = new BoxCollider2D(new Vector2(position.x, position.y), new Vector2(64, 64), zenObject);
		boxCollider->OnBoxCollisionStart = std::bind(&Ground::HandleBoxCollisionStart, this, std::placeholders::_1);
		ZenPhysics2D::Get()->RegisterCollider(boxCollider);
	}

private:
	sf::Vector2f position;
	BoxCollider2D* boxCollider = nullptr;
	ZenObject* zenObject = nullptr;

	void HandleBoxCollisionStart(BoxCollider2D* other)
	{

	}
};

