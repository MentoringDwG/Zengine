#include "CircleCollider2D.h"
#include <cmath>

CircleCollider2D::CircleCollider2D(Vector2* position, float radius, ZenObject* owner)
{
	SetPosition(sf::Vector2f(position->x, position->y));
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


void CircleCollider2D::SetPosition(sf::Vector2f vector)
{
	debugCircle.setPosition(vector.x + GetOwner()->size.x / 2, vector.y + GetOwner()->size.y / 2);
	GetPosition()->x = vector.x + GetOwner()->size.x / 2;
	GetPosition()->y = vector.y + GetOwner()->size.y / 2;
}

bool CircleCollider2D::CheckCircleCollision(CircleCollider2D* otherCollider)
{
	float distance = GetPosition()->GetDistance(otherCollider->GetPosition());
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
		OnCollisionStart(otherCollider);
	}

	return bIsColliding;
}

bool CircleCollider2D::CheckBoxCollision(BoxCollider2D* otherCollider)
{
	testPoint->x = GetPosition()->x;
	testPoint->y = GetPosition()->y;

	if (GetPosition()->x < otherCollider->GetPosition()->x)
	{
		testPoint->x = otherCollider->GetPosition()->x;
	}
	else if (GetPosition()->x > otherCollider->GetPosition()->x + otherCollider->GetSize()->x)
	{
		testPoint->x = otherCollider->GetPosition()->x + otherCollider->GetSize()->x;
	}

	if (GetPosition()->y < otherCollider->GetPosition()->y)
	{
		testPoint->y = otherCollider->GetPosition()->y;
	}
	else if (GetPosition()->y > otherCollider->GetPosition()->y + otherCollider->GetSize()->y)
	{
		testPoint->y = otherCollider->GetPosition()->y + otherCollider->GetSize()->y;
	}

	if (testPoint->GetDistance(GetPosition()) <= radius)
	{
		bIsColliding = true;
	}
	else
	{
		bIsColliding = false;
	}

	if (HasCollision())
	{
		OnCollisionStart(otherCollider);
	}
	else
	{
		OnCollisionEnd(otherCollider);
	}

	return bIsColliding;
}

bool CircleCollider2D::HasCollision()
{
	return bIsColliding;
}