#include "CircleCollider2D.h"
#include <cmath>

CircleCollider2D::CircleCollider2D(Vector2* position, float radius, ZenObject* owner)
{
	this->position = position;
	this->radius = radius;
	SetOwner(owner);
}

bool CircleCollider2D::CheckCollision(CircleCollider2D* otherCollider)
{
	float distance = position->GetDistance(otherCollider->position);
	if (distance < radius + otherCollider->radius)
	{
		if (distance >= abs(otherCollider->radius - radius))
		{
			bIsColliding = true;
		}
	}
	else
	{
		bIsColliding = false;
	}

	if (HasCollision())
	{
		OnCollisionStart(otherCollider);
	}
}

bool CircleCollider2D::HasCollision()
{
	return bIsColliding;
}

ZenObject* CircleCollider2D::GetOwner()
{
	return owner;
}

void CircleCollider2D::SetOwner(ZenObject* inOwner)
{
	owner = inOwner;
}