#include "CircleCollider2D.h"
#include <cmath>

CircleCollider2D::CircleCollider2D(Vector2* position, float radius, ZenObject* owner)
{
	this->position = position;
	this->radius = radius;
	SetOwner(owner);

	circle.setRadius(radius);
	circle.setOrigin(radius/2, 0);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Green);
	circle.setOutlineThickness(1);
	circle.setPosition(owner->Position);
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

void CircleCollider2D::SetPosition(sf::Vector2f vector)
{
	circle.setPosition(vector);
	position->x = vector.x;
	position->y = vector.y;
}