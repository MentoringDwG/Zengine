#include "Castle.h"
#include "../Colliders/BoxCollider2D.h"
#include "../ZenObject/ZenObject.h"
#include "../Physics2D/ZenPhysics2D.h"

#include <iostream>

Castle::Castle(Vector2 size, Vector2 position)
{
	zenObject = new ZenObject(20, "Castle", sf::Vector2f(size.x, size.y));

	boxCollider = new BoxCollider2D(position, size, zenObject, Collider::ColliderTags::CASTLE);
	boxCollider->OnCollisionStart.AddListener(&Castle::HandleCollisionStart, this);
	boxCollider->OnCollisionEnd.AddListener(&Castle::HandleCollisionEnd, this);
	ZenPhysics2D::Get()->RegisterCollider(boxCollider);
}

void Castle::HandleCollisionStart(Collider* other)
{
	if (other->GetOwner()->name == "Mario" && !isCollisionWithMario)
	{
		isCollisionWithMario = true;
		std::cout << "Castle" << std::endl;
	}
}

void Castle::HandleCollisionEnd(Collider* other)
{
	if (other->GetOwner()->name == "Mario")
	{
		isCollisionWithMario = false;
	}
}