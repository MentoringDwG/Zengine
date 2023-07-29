#include "CircleCollider2D.h"
#include <cmath>

CircleCollider2D::CircleCollider2D(Vector2* position, float radius, ZenObject* owner)
{
	this->position = position;
	this->radius = radius;
	SetOwner(owner);

	debugCircle.setRadius(radius);
	debugCircle.setOrigin(radius, radius);
	debugCircle.setFillColor(sf::Color::Transparent);
	debugCircle.setOutlineColor(sf::Color::Green);
	debugCircle.setOutlineThickness(1);

	SetPosition(sf::Vector2f(position->x, position->y));

	testPoint = new Vector2(position->x, position->y);
}

void CircleCollider2D::SetOwner(ZenObject* inOwner)
{
	owner = inOwner;
}

void CircleCollider2D::SetPosition(sf::Vector2f vector)
{
	debugCircle.setPosition(vector.x + owner->size.x / 2, vector.y + owner->size.y / 2);
	position->x = vector.x + owner->size.x / 2;
	position->y = vector.y + owner->size.y / 2;
}

bool CircleCollider2D::CheckCircleCollision(CircleCollider2D* otherCollider)
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
	{	bIsColliding = false;
	}

	if (HasCollision())
	{
		OnCircleCollisionStart(otherCollider);
	}

	return bIsColliding;
}

bool CircleCollider2D::CheckBoxCollision(BoxCollider2D* otherCollider)
{
	testPoint->x = this->position->x;
	testPoint->y = this->position->y;

	if (this->position->x < otherCollider->GetPosition()->x)
	{
		testPoint->x = otherCollider->GetPosition()->x;
	}
	else if (this->position->x > otherCollider->GetPosition()->x + otherCollider->GetSize()->x)
	{
		testPoint->x = otherCollider->GetPosition()->x + otherCollider->GetSize()->x;
	}

	if (this->position->y < otherCollider->GetPosition()->y)
	{
		testPoint->y = otherCollider->GetPosition()->y;
	}
	else if (this->position->y > otherCollider->GetPosition()->y + otherCollider->GetSize()->y)
	{
		testPoint->y = otherCollider->GetPosition()->y + otherCollider->GetSize()->y;
	}

	if (testPoint->GetDistance(position) <= radius)
	{
		bIsColliding = true;
	}
	else
	{
		bIsColliding = false;
	}

	if (HasCollision())
	{
		OnBoxCollisionStart(otherCollider);
	}
	else
	{
		OnBoxCollisionEnd(otherCollider);
	}

	return bIsColliding;
}

bool CircleCollider2D::HasCollision()
{
	return bIsColliding;
}

ZenObject* CircleCollider2D::GetOwner()
{
	return owner;
}